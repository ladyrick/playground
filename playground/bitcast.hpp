#include "common.hpp"

#ifndef __PLAYGROUND_BITCAST__
#define __PLAYGROUND_BITCAST__

namespace playground {

class BitCast {
  private:
    struct bits {
        unsigned char b7 : 1;
        unsigned char b6 : 1;
        unsigned char b5 : 1;
        unsigned char b4 : 1;
        unsigned char b3 : 1;
        unsigned char b2 : 1;
        unsigned char b1 : 1;
        unsigned char b0 : 1;
    };
    size_t length;
    std::ostringstream oss;
    std::ostringstream data;

  public:
    template <class T>
    explicit BitCast(const T &input) {
        data << input << " type: " << typeid(input).name();
        const T *pTInput = &input;
        auto *pBitsinput = (bits *)pTInput;
        int n = sizeof(T) / sizeof(bits);
        length = 9 * n - 1;
        for (int i = n - 1; i >= 0; --i) {
            oss << (int)((pBitsinput + i)->b0) << (int)((pBitsinput + i)->b1)
                << (int)((pBitsinput + i)->b2) << (int)((pBitsinput + i)->b3)
                << (int)((pBitsinput + i)->b4) << (int)((pBitsinput + i)->b5)
                << (int)((pBitsinput + i)->b6) << (int)((pBitsinput + i)->b7)
                << ' ';
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const BitCast &c) {
        os << c.data.str() << std::endl;
        os << "M" << std::string(c.length - 2, ' ') << "L" << std::endl;
        os << c.oss.str() << std::endl;
        return os;
    }
};
} // namespace playground

#endif
