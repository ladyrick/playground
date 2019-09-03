#include <algorithm>
#include <deque>
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
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifndef __PLAYGROUND_COMMON__
#define __PLAYGROUND_COMMON__

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
} // namespace __

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

template <class Container>
std::ostream &display(const Container &container,
                      std::ostream &os = std::cout) {
    bool first = true;
    for (const auto &e : container) {
        if (first) {
            os << e;
            first = false;
        } else {
            os << ' ' << e;
        }
    }
    return os;
}

template <class ForwardIterator>
std::ostream &display(const ForwardIterator begin, const ForwardIterator end,
                      std::ostream &os = std::cout) {
    bool first = true;
    for (ForwardIterator it = begin; it != end; ++it) {
        if (first) {
            os << *it;
            first = false;
        } else {
            os << ' ' << *it;
        }
    }
    return os;
}

} // namespace playground

#endif
