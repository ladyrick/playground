#include "playground/bignumber.hpp"
using namespace std;
using namespace playground;

int main() {
    BigNumber result = 1;
    for (int i = 1; i <= 100; i++) {
        result = result * i;
        cout << result << endl;
    }
}
