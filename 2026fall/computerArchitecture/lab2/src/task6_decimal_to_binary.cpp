#include <iostream>
using namespace std;

int main() {
    int n;
    int bits[16];

    cout << "Decimal number: ";
    cin >> n;

    if (n < 0 || n > 65535) {
        cout << "Number must be between 0 and 65535.\n";
        return 0;
    }

    for (int i = 15; i >= 0; i--) {
        bits[i] = n % 2;
        n = n / 2;
    }

    cout << "16 bit binary: ";
    for (int i = 0; i < 16; i++) {
        cout << bits[i];
        if ((i + 1) % 4 == 0) cout << " ";
    }
    cout << endl;

    return 0;
}
