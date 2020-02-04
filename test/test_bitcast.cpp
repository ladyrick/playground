#include "../playground/bitcast.hpp"

using namespace playground;
using namespace std;

int main() {
    cout << BitCast(123) << endl;
    cout << BitCast((long long)123) << endl;
    cout << BitCast(123.0f) << endl;
    cout << BitCast(123.0) << endl;
    cout << BitCast('3') << endl;
    cout << BitCast("123") << endl;
    cout << BitCast(string("123")) << endl;
    cout << BitCast(bitset<66>().set());
    return 0;
}
