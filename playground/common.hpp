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

#define __EXEC_HELPER2__(expression, counter)                                  \
    namespace __exec_helper_namespace_##counter {                              \
        struct __exec_helper_class__ {                                         \
            __exec_helper_class__() { expression; }                            \
        } __executor__;                                                        \
    }
#define __EXEC_HELPER1__(expression, counter)                                  \
    __EXEC_HELPER2__(expression, counter)

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

int randint(int start, int end) {
    return std::uniform_int_distribution<>(start, end)(__::gen);
}

std::string input() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::vector<std::string> split(const std::string &str,
                               const std::string &delim) {
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

#define __PLAYGROUND_OPERATOR_LEFT_SHIFT__(os, cont)                           \
    bool first = true;                                                         \
    for (const auto &elem : cont) {                                            \
        if (first) {                                                           \
            os << '[' << elem;                                                 \
            first = false;                                                     \
        } else {                                                               \
            os << ',' << elem;                                                 \
        }                                                                      \
    }                                                                          \
    os << ']';                                                                 \
    return os;

#define __PLAYGROUND_PARTIAL_SPECIALIZE_ONE__(Cont)                            \
    template <class T>                                                         \
    std::ostream &operator<<(std::ostream &os, const Cont<T> &cont) {          \
        __PLAYGROUND_OPERATOR_LEFT_SHIFT__(os, cont)                           \
    }

#define __PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(Cont)                            \
    template <class T1, class T2>                                              \
    std::ostream &operator<<(std::ostream &os, const Cont<T1, T2> &cont) {     \
        __PLAYGROUND_OPERATOR_LEFT_SHIFT__(os, cont)                           \
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
    os << "pair<" << pair.first << ',' << pair.second << '>';
    return os;
}

__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::map)
__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::multimap)
__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::unordered_map)
__PLAYGROUND_PARTIAL_SPECIALIZE_TWO__(std::unordered_multimap)
} // namespace playground

#endif
