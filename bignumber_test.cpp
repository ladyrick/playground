#include "playground/bignumber.hpp"
using namespace std;

int main() {
    BigNumber a = 123457;
    BigNumber b = 123456;
    BigNumber c = a - b;
    cout << a << " - " << b << " = " << c << endl;
    for (auto i:c){
        cout << int(i) << ' ';
    }
    cout << endl;
}
