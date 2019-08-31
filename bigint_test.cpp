#include "playground/bigint.hpp"
#include "playground/lru_cache.hpp"

using namespace std;
using namespace playground;

LRUCache<int, BigInt> lru_cache(1000);

BigInt Fibonacci(int x) {
    if (lru_cache.hit(x)) {
        return lru_cache.hit_and_get(x);
    } else {
        BigInt y = 1;
        if (x > 1) {
            auto y1 = Fibonacci(x - 1);
            auto y2 = Fibonacci(x - 2);
            y = y1 + y2;
        }
        lru_cache.not_hit_and_push(x, y);
        return y;
    }
}

BigInt Factorial(int n) {
    BigInt result = 1;
    while (n) {
        result = result * n;
        n--;
    }
    return result;
}

int main() {
    int n = 1000;
    cout << "Fibonacci(" << n << ") = " << Fibonacci(n) << endl;
    cout << "Factorial(" << n << ") = " << Factorial(n) << endl;
}
