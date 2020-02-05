#include "../playground/common.hpp"

using namespace std;
using playground::Color;

int main() {
    cout << Color().fore(Color::F::Default) << "foreground Default" << endl;
    cout << Color().fore(Color::F::Black) << "foreground Black" << endl;
    cout << Color().fore(Color::F::Red) << "foreground Red" << endl;
    cout << Color().fore(Color::F::Green) << "foreground Green" << endl;
    cout << Color().fore(Color::F::Yellow) << "foreground Yellow" << endl;
    cout << Color().fore(Color::F::Blue) << "foreground Blue" << endl;
    cout << Color().fore(Color::F::Magenta) << "foreground Magenta" << endl;
    cout << Color().fore(Color::F::Cyan) << "foreground Cyan" << endl;
    cout << Color().fore(Color::F::LightGray) << "foreground LightGray" << endl;
    cout << Color().fore(Color::F::DarkGray) << "foreground DarkGray" << endl;
    cout << Color().fore(Color::F::LightRed) << "foreground LightRed" << endl;
    cout << Color().fore(Color::F::LightGreen) << "foreground LightGreen" << endl;
    cout << Color().fore(Color::F::LightYellow) << "foreground LightYellow" << endl;
    cout << Color().fore(Color::F::LightBlue) << "foreground LightBlue" << endl;
    cout << Color().fore(Color::F::LightMagenta) << "foreground LightMagenta" << endl;
    cout << Color().fore(Color::F::LightCyan) << "foreground LightCyan" << endl;
    cout << Color().fore(Color::F::White) << "foreground White" << endl;

    cout << Color().back(Color::B::Default) << "background Default" << Color::Clear << endl;
    cout << Color().back(Color::B::Black) << "background Black" << Color::Clear << endl;
    cout << Color().back(Color::B::Red) << "background Red" << Color::Clear << endl;
    cout << Color().back(Color::B::Green) << "background Green" << Color::Clear << endl;
    cout << Color().back(Color::B::Yellow) << "background Yellow" << Color::Clear << endl;
    cout << Color().back(Color::B::Blue) << "background Blue" << Color::Clear << endl;
    cout << Color().back(Color::B::Magenta) << "background Magenta" << Color::Clear << endl;
    cout << Color().back(Color::B::Cyan) << "background Cyan" << Color::Clear << endl;
    cout << Color().back(Color::B::LightGray) << "background LightGray" << Color::Clear << endl;
    cout << Color().back(Color::B::DarkGray) << "background DarkGray" << Color::Clear << endl;
    cout << Color().back(Color::B::LightRed) << "background LightRed" << Color::Clear << endl;
    cout << Color().back(Color::B::LightGreen) << "background LightGreen" << Color::Clear << endl;
    cout << Color().back(Color::B::LightYellow) << "background LightYellow" << Color::Clear << endl;
    cout << Color().back(Color::B::LightBlue) << "background LightBlue" << Color::Clear << endl;
    cout << Color().back(Color::B::LightMagenta) << "background LightMagenta" << Color::Clear << endl;
    cout << Color().back(Color::B::LightCyan) << "background LightCyan" << Color::Clear << endl;
    cout << Color().back(Color::B::White) << "background White" << Color::Clear << endl;

    cout << Color().fore(Color::F::Green).style(Color::S::Default) << "Green style Default" << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Bold) << "Green style Bold" << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Dim) << "Green style Dim" << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Underlined) << "Green style Underlined" << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Blink) << "Green style Blink" << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Reverse) << "Green style Reverse" << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Hidden) << "Green style Hidden" << endl;

    for (int i = 0; i <= 256; i++) {
        cout << Color().c_256(i) << 'X';
        if (i % 32 == 0) {
            cout << Color::Clear << endl;
        }
    }
    for (int i = 0; i <= 256; i++) {
        cout << Color().c_256(-1, i) << 'X';
        if (i % 32 == 0) {
            cout << Color::Clear << endl;
        }
    }
    for (int i = 0; i <= 256; i++) {
        cout << Color().c_256(i, i) << 'X';
        if (i % 32 == 0) {
            cout << Color::Clear << endl;
        }
    }
}
