#include "common.hpp"

#ifndef __PLAYGROUND_BIGNUMBER__
#define __PLAYGROUND_BIGNUMBER__

namespace playground {
using playground::input;

class BigNumber {
  private:
    typedef uint8_t base_t;
    typedef int16_t double_base_t;
    typedef std::vector<base_t> digs_t;

    bool isneg;
    digs_t digs;

    static const base_t BASE = 100;
    static int digs_comp(const digs_t &a, const digs_t &b) {
        if (a.size() < b.size())
            return -1;
        if (a.size() > b.size())
            return 1;
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a[i] < b[i])
                return -1;
            if (a[i] > b[i])
                return 1;
        }
        return 0;
    }
    static void digs_add_assign(digs_t &a, const digs_t &b, int pos_a = 0,
                                int pos_b = 0) {
        if (b.size() - pos_b > a.size() - pos_a) {
            a.reserve((b.size() - pos_b + pos_a + 1));
        }
        int size_b = b.size();
        int carry = 0;
        while (pos_b < size_b || carry) {
            int b_pos_b = pos_b < size_b ? b[pos_b] : 0;
            if (pos_a == a.size()) {
                a.push_back(b_pos_b + carry);
            } else {
                a[pos_a] += b_pos_b + carry;
            }
            carry = 0;
            if (a[pos_a] >= BASE) {
                a[pos_a] -= BASE;
                carry = 1;
            }
            pos_a++;
            pos_b++;
        }
    }
    static bool digs_minus(const digs_t &a, const digs_t &b, digs_t &r) {
        auto comp = digs_comp(a, b);
        if (comp == 0) {
            r = {0};
            return false;
        }
        r = comp > 0 ? a : b;
        const digs_t &lessone = comp > 0 ? b : a;
        int borrow = 0;
        size_t i = 0;
        while (i < lessone.size()) {
            if (r[i] < lessone[i] + borrow) {
                r[i] = r[i] + BASE - lessone[i] - borrow;
                borrow = 1;
            } else {
                r[i] -= lessone[i] + borrow;
                borrow = 0;
            }
            i++;
        }
        while (borrow) {
            if (r[i] < borrow) {
                r[i] = r[i] + BASE - borrow;
                borrow = 1;
            } else {
                r[i] -= borrow;
                borrow = 0;
            }
            i++;
        }
        while (r.back() == 0) {
            r.pop_back();
        }
        return comp < 0;
    }

    static void digs_multi(const digs_t &a, const digs_t &b, digs_t &r) {
        const digs_t &big = a.size() > b.size() ? a : b;
        const digs_t &sml = a.size() > b.size() ? b : a;
        int step = 0;
        while (step < big.size()) {
            for (int i = step; i >= 0 && step - i < sml.size(); i--) {
                double_base_t tmp =
                    (double_base_t)big[i] * (double_base_t)sml[step - i];
                digs_t tmp_digs = {base_t(tmp % BASE), base_t(tmp / BASE)};
                if (tmp_digs.back() == 0)
                    tmp_digs.pop_back();
                digs_add_assign(r, tmp_digs, step);
            }
            step++;
        }
        int step2 = 0;
        while (step2 < sml.size() - 1) {
            for (int i = 1; i < sml.size() - step2; i++) {
                double_base_t tmp = (double_base_t)big[big.size() - i] *
                                    (double_base_t)sml[i + step2];
                digs_t tmp_digs = {base_t(tmp % BASE), base_t(tmp / BASE)};
                if (tmp_digs.back() == 0)
                    tmp_digs.pop_back();
                digs_add_assign(r, tmp_digs, step + step2);
            }
            step2++;
        }
    }

  public:
    BigNumber(int64_t value = 0) : isneg(value < 0) {
        if (value == 0) {
            digs.push_back(0);
            return;
        }
        if (isneg) {
            value = -value;
        }
        while (value) {
            digs.push_back(value % BASE);
            value /= BASE;
        }
    }
    BigNumber(const BigNumber &bg) : digs(bg.digs) { isneg = bg.isneg; }
    std::string to_string() const {
        int width = 0;
        int base = BASE - 1;
        while (base) {
            width += 1;
            base /= 10;
        }
        std::stringstream oss;
        if (isneg) {
            oss << '-';
        }
        bool ischar = std::is_same<char, base_t>::value ||
                      std::is_same<signed char, base_t>::value ||
                      std::is_same<unsigned char, base_t>::value;
        oss << (ischar ? int(digs.back()) : digs.back());
        for (int i = digs.size() - 2; i >= 0; i--) {
            oss << std::setw(width) << std::setfill('0')
                << (ischar ? int(digs[i]) : digs[i]);
        }
        return oss.str();
    }
    BigNumber operator+(const BigNumber &bg) {
        BigNumber result;
        if (isneg == bg.isneg) {
            result = *this;
            digs_add_assign(result.digs, bg.digs);
            result.isneg = isneg;
        } else {
            bool rev = digs_minus(digs, bg.digs, result.digs);
            result.isneg = rev ^ isneg;
        }
        return result;
    }
    BigNumber operator-(const BigNumber &bg) {
        BigNumber result;
        if (isneg == bg.isneg) {
            auto rev = digs_minus(digs, bg.digs, result.digs);
            result.isneg = rev ^ isneg;
        } else {
            result = *this;
            digs_add_assign(result.digs, bg.digs);
            result.isneg = isneg;
        }
        return result;
    }
    BigNumber operator*(const BigNumber &bg) {
        BigNumber result;
        result.isneg = isneg ^ bg.isneg;
        digs_multi(digs, bg.digs, result.digs);
        return result;
    }
};

std::ostream &operator<<(std::ostream &os, const BigNumber &bg) {
    os << bg.to_string();
    return os;
}
} // namespace playground

#endif
