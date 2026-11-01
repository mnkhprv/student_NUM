#include <iostream>
using namespace std;

int main() {
    int n;
    int bits[16];

    cout << "Negative number: ";
    cin >> n;

    if (n < -32768 || n >= 0) {
        cout << "Number must be between -32768 and -1.\n";
        return 0;
    }

    unsigned int value = 65536 + n;

    for (int i = 15; i >= 0; i--) {
        bits[i] = value % 2;
        value = value / 2;
    }

    cout << "16 bit signed binary: ";
    for (int i = 0; i < 16; i++) {
        cout << bits[i];
        if ((i + 1) % 4 == 0) cout << " ";
    }
    cout << endl;

    return 0;
}
