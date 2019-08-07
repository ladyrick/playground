#include <algorithm>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
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
} // namespace playground

#endif
