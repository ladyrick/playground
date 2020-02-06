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

    cout << Color().back(Color::B::Default) << "background Default" << Color::Reset << endl;
    cout << Color().back(Color::B::Black) << "background Black" << Color::Reset << endl;
    cout << Color().back(Color::B::Red) << "background Red" << Color::Reset << endl;
    cout << Color().back(Color::B::Green) << "background Green" << Color::Reset << endl;
    cout << Color().back(Color::B::Yellow) << "background Yellow" << Color::Reset << endl;
    cout << Color().back(Color::B::Blue) << "background Blue" << Color::Reset << endl;
    cout << Color().back(Color::B::Magenta) << "background Magenta" << Color::Reset << endl;
    cout << Color().back(Color::B::Cyan) << "background Cyan" << Color::Reset << endl;
    cout << Color().back(Color::B::LightGray) << "background LightGray" << Color::Reset << endl;
    cout << Color().back(Color::B::DarkGray) << "background DarkGray" << Color::Reset << endl;
    cout << Color().back(Color::B::LightRed) << "background LightRed" << Color::Reset << endl;
    cout << Color().back(Color::B::LightGreen) << "background LightGreen" << Color::Reset << endl;
    cout << Color().back(Color::B::LightYellow) << "background LightYellow" << Color::Reset << endl;
    cout << Color().back(Color::B::LightBlue) << "background LightBlue" << Color::Reset << endl;
    cout << Color().back(Color::B::LightMagenta) << "background LightMagenta" << Color::Reset << endl;
    cout << Color().back(Color::B::LightCyan) << "background LightCyan" << Color::Reset << endl;
    cout << Color().back(Color::B::White) << "background White" << Color::Reset << endl;

    cout << Color().fore(Color::F::Green).style(Color::S::Bold) << "Green style Bold" << Color().style(Color::S::NoBold) << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Dim) << "Green style Dim" << Color().style(Color::S::NoDim) << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Italic) << "Green style Italic" << Color().style(Color::S::NoItalic) << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Underline) << "Green style Underline" << Color().style(Color::S::NoUnderline) << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Blink) << "Green style Blink" << Color().style(Color::S::NoBlink) << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Reverse) << "Green style Reverse" << Color().style(Color::S::NoReverse) << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Hidden) << "Green style Hidden" << Color().style(Color::S::NoHidden) << endl;
    cout << Color().fore(Color::F::Green).style(Color::S::Delete) << "Green style Delete" << Color().style(Color::S::NoDelete) << endl;

    for (int i = 0; i <= 256; i++) {
        cout << Color().c_256(i) << 'X';
        if (i % 32 == 0) {
            cout << Color::Reset << endl;
        }
    }
    for (int i = 0; i <= 256; i++) {
        cout << Color().c_256(-1, i) << 'X';
        if (i % 32 == 0) {
            cout << Color::Reset << endl;
        }
    }
    for (int i = 0; i <= 256; i++) {
        cout << Color().c_256(i, i) << 'X';
        if (i % 32 == 0) {
            cout << Color::Reset << endl;
        }
    }
}
