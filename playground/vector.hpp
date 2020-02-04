#include "common.hpp"

#ifndef __PLAYGROUND_VECTOR__
#define __PLAYGROUND_VECTOR__

namespace playground {
std::vector<int> generateRandomVector(int num_nodes = 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    if (!num_nodes) {
        std::uniform_int_distribution<> idis(1, 30);
        num_nodes = idis(gen);
    }
    std::vector<int> vec(num_nodes);
    for (int &p : vec) {
        p = playground::randint(-num_nodes, num_nodes);
    }
    return vec;
}
} // namespace playground

#endif
