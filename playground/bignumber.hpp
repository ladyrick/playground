#include "common.hpp"

typedef uint8_t base_t;
typedef int16_t double_base_t;
class BigNumber : public std::vector<base_t> {
  private:
    static const base_t BASE = 100;
    typedef std::vector<base_t> digs_t;

    bool isneg;
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
    static void digs_add(const digs_t &a, const digs_t &b, digs_t &r) {
        r = a.size() > b.size() ? a : b;
        const digs_t &lessone = a.size() > b.size() ? b : a;
        int carry = 0;
        size_t i = 0;
        while (i < lessone.size()) {
            r[i] += lessone[i] + carry;
            carry = 0;
            if (r[i] >= BASE) {
                r[i] -= BASE;
                carry = 1;
            }
            i++;
        }
        while (carry) {
            if (r.size() == i) {
                r.push_back(0);
            }
            r[i] += carry;
            carry = 0;
            if (r[i] >= BASE) {
                r[i] -= BASE;
                carry = 1;
            }
            i++;
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

    static bool digs_multi(const digs_t &a, const digs_t &b, digs_t &r) {
        BigNumber result;
        BigNumber carry;
        const digs_t &bigone = a.size() > b.size() ? a : b;
        const digs_t &lessone = a.size() > b.size() ? b : a;
        int step = 1;
        while (step <= bigone.size()) {
            for (int i = 0; i < step; i++) {
            }
        }
    }

  public:
    BigNumber(int64_t value = 0) : isneg(value < 0) {
        if (value == 0) {
            push_back(0);
            return;
        }
        if (isneg) {
            value = -value;
        }
        while (value) {
            push_back(value % BASE);
            value /= BASE;
        }
    }
    BigNumber(const BigNumber &bg) : digs_t(bg) { isneg = bg.isneg; }
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
        oss << (ischar ? int(back()) : back());
        for (int i = size() - 2; i >= 0; i--) {
            oss << std::setw(width) << std::setfill('0')
                << (ischar ? int(operator[](i)) : operator[](i));
        }
        return oss.str();
    }
    BigNumber operator+(const BigNumber &bg) {
        BigNumber result;
        if (isneg == bg.isneg) {
            digs_add(*this, bg, result);
            result.isneg = isneg;
        } else {
            bool rev = digs_minus(*this, bg, result);
            result.isneg = rev ^ isneg;
        }
        return result;
    }
    BigNumber operator-(const BigNumber &bg) {
        BigNumber result;
        if (isneg == bg.isneg) {
            auto rev = digs_minus(*this, bg, result);
            result.isneg = rev ^ isneg;
        } else {
            digs_add(*this, bg, result);
            result.isneg = isneg;
        }
        return result;
    }
    BigNumber operator*(const BigNumber &bg) {
        BigNumber result;
        result.isneg = isneg ^ bg.isneg;
        digs_multi(*this, bg, result);
        return result;
    }
};

std::ostream &operator<<(std::ostream &os, const BigNumber &bg) {
    os << bg.to_string();
    return os;
}