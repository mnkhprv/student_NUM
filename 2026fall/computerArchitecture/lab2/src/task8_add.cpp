#include <iostream>
#include <string>
using namespace std;

int binaryToDecimal(string s) {
    int value = 0;

    for (int i = 0; i < 16; i++)
        value = (value << 1) + (s[i] - '0');

    if (s[0] == '1') value = value - 65536;
    return value;
}

void printBinary(int n) {
    unsigned int value;
    int bits[16];

    if (n < 0) value = 65536 + n;
    else value = n;

    for (int i = 15; i >= 0; i--) {
        bits[i] = value & 1;
        value = value >> 1;
    }

    for (int i = 0; i < 16; i++) {
        cout << bits[i];
        if ((i + 1) % 4 == 0) cout << " ";
    }
}

int main() {
    string a, b;

    cout << "First 16 bit number: ";
    cin >> a;
    cout << "Second 16 bit number: ";
    cin >> b;

    if (a.length() != 16 || b.length() != 16) {
        cout << "Input must contain 16 bits.\n";
        return 0;
    }

    int x = binaryToDecimal(a);
    int y = binaryToDecimal(b);
    int exactSum = x + y;
    int sum = exactSum;

    if (sum > 32767) sum = sum - 65536;
    if (sum < -32768) sum = sum + 65536;

    cout << "Decimal result: " << sum << endl;
    cout << "Binary result: ";
    printBinary(sum);
    cout << endl;

    if (exactSum > 32767 || exactSum < -32768)
        cout << "Overflow occurred.\n";

    return 0;
}
