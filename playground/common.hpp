#include <algorithm>
#include <chrono>
#include <deque>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifndef __PLAYGROUND_COMMON__
#define __PLAYGROUND_COMMON__

#define __EXEC_HELPER2__(expression, counter)       \
    namespace __exec_helper_namespace_##counter {   \
        struct __exec_helper_class__ {              \
            __exec_helper_class__() { expression; } \
        } __executor__;                             \
    }
#define __EXEC_HELPER1__(expression, counter) __EXEC_HELPER2__(expression, counter)

// used to exec expression before entry main().
#define EXEC(expression) __EXEC_HELPER1__(expression, __COUNTER__)

namespace playground {

namespace __ {
struct AutoFree {
    AutoFree() {}
    virtual ~AutoFree() {}
    void *operator new(size_t);
};

struct MemFreer {
    std::vector<AutoFree *> pool;
    ~MemFreer() {
        for (auto p : pool) {
            delete p;
        }
    }
} mem_freer;

void *AutoFree::operator new(size_t size) {
    void *p = malloc(size);
    mem_freer.pool.push_back((AutoFree *)p);
    return p;
}

std::random_device rd;
std::mt19937 gen(rd());
} // namespace __

int randint(int start, int end) { return std::uniform_int_distribution<>(start, end)(__::gen); }

std::string input() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::vector<std::string> split(const std::string &str, const std::string &delim) {
    int begin = 0;
    std::vector<std::string> result;
    int npos;
    while ((npos = str.find(delim, begin)) != str.npos) {
        result.emplace_back(std::move(str.substr(begin, npos - begin)));
        begin = npos + delim.length();
    }
    result.emplace_back(str.substr(begin, str.length() - begin));
    return result;
}

class Color {
  public:
    enum class F {
        NoChange = 1,
        Default = 39,
        Black = 30,
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        Cyan = 36,
        LightGray = 37,
        DarkGray = 90,
        LightRed = 91,
        LightGreen = 92,
        LightYellow = 93,
        LightBlue = 94,
        LightMagenta = 95,
        LightCyan = 96,
        White = 97,
    };
    enum class B {
        NoChange = 1,
        Default = 49,
        Black = 40,
        Red = 41,
        Green = 42,
        Yellow = 43,
        Blue = 44,
        Magenta = 45,
        Cyan = 46,
        LightGray = 47,
        DarkGray = 100,
        LightRed = 101,
        LightGreen = 102,
        LightYellow = 103,
        LightBlue = 104,
        LightMagenta = 105,
        LightCyan = 106,
        White = 107,
    };
    enum class S {
        NoChange = -1,
        Bold = 1,
        Dim = 2,
        Italic = 3,
        Underline = 4,
        Blink = 5,
        FastBlink = 6,
        Reverse = 7,
        Hidden = 8,
        Delete = 9,
        NoBold = 21,
        NoDim = 22,
        NoItalic = 23,
        NoUnderline = 24,
        NoBlink = 25,
        NoReverse = 27,
        NoHidden = 28,
        NoDelete = 29,
    };
    Color(bool reset = false) : style_code(reset ? 0 : int(S::NoChange)) {}
    const static Color Reset;
    Color &c_256(int foreground = -1, int background = -1) {
        if (foreground >= 0 && foreground <= 256) {
            this->foreground_code = -foreground;
        }
        if (background >= 0 && background <= 256) {
            this->background_code = -background;
        }
        return *this;
    }
    Color &fore(F foreground) {
        this->foreground_code = int(foreground);
        return *this;
    }
    Color &back(B background) {
        this->background_code = int(background);
        return *this;
    }
    Color &style(S style) {
        this->style_code = int(style);
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Color &color) {
        if (os.rdbuf() != std::cout.rdbuf()) {
            return os;
        }
        if (color.style_code == 0) {
            os << "\e[0m";
            return os;
        }
        std::ostringstream oss;
        if (color.foreground_code != int(Color::F::NoChange)) {
            if (color.foreground_code > 0) {
                oss << "\e[" << color.foreground_code << 'm';
            } else {
                oss << "\e[38;5;" << -color.foreground_code << 'm';
            }
        }
        if (color.background_code != int(Color::B::NoChange)) {
            if (color.background_code > 0) {
                oss << "\e[" << color.background_code << 'm';
            } else {
                oss << "\e[48;5;" << -color.background_code << 'm';
            }
        }
        if (color.style_code != int(Color::S::NoChange)) {
            oss << "\e[" << color.style_code << 'm';
        }
        os << oss.str();
        return os;
    }

  private:
    int foreground_code = int(F::NoChange);
    int background_code = int(B::NoChange);
    int style_code = int(S::NoChange);
};

const Color Color::Reset(true);
} // namespace playground

// ostream for all containers.
#define __PLAYGROUND_OPERATOR_LEFT_SHIFT__(os, cont) \
    os << '[';                                       \
    bool first = true;                               \
    for (const auto &elem : cont) {                  \
        if (first) {                                 \
            os << elem;                              \
            first = false;                           \
        } else {                                     \
            os << ',' << elem;                       \
        }                                            \
    }                                                \
    os << ']';                                       \
    return os;

#define __PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(Cont)                   \
    template <class T>                                                \
    std::ostream &operator<<(std::ostream &os, const Cont<T> &cont) { \
        __PLAYGROUND_OPERATOR_LEFT_SHIFT__(os, cont)                  \
    }

#define __PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(Cont)                        \
    template <class T1, class T2>                                          \
    std::ostream &operator<<(std::ostream &os, const Cont<T1, T2> &cont) { \
        __PLAYGROUND_OPERATOR_LEFT_SHIFT__(os, cont)                       \
    }

__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::deque)
__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::forward_list)
__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::list)
__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::multiset)
__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::set)
__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::unordered_multiset)
__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::unordered_set)
__PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(std::vector)

template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &pair) {
    os << "<" << pair.first << ',' << pair.second << '>';
    return os;
}

__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::map)
__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::multimap)
__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::unordered_map)
__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::unordered_multimap)

#endif
