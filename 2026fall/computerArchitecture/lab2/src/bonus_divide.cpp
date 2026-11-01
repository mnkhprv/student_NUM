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

void printBinary32(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        cout << ((n >> i) & 1);
        if (i % 4 == 0) cout << " ";
    }
}

int main() {
    string a, b;

    cout << "Dividend (16 bit): ";
    cin >> a;
    cout << "Divisor (16 bit): ";
    cin >> b;

    if (a.length() != 16 || b.length() != 16) {
        cout << "Input must contain 16 bits.\n";
        return 0;
    }

    int x = binaryToDecimal(a);
    int y = binaryToDecimal(b);

    if (y == 0) {
        cout << "Cannot divide by zero.\n";
        return 0;
    }

    unsigned int dividend = x < 0 ? -x : x;
    unsigned int divisor = y < 0 ? -y : y;
    unsigned int quotient = 0;
    unsigned int remainder = 0;

    for (int i = 15; i >= 0; i--) {
        remainder = (remainder << 1) + ((dividend >> i) & 1);

        if (remainder >= divisor) {
            remainder = remainder + (~divisor + 1);
            quotient = quotient + (1 << i);
        }
    }

    int quotientAnswer = quotient;
    int remainderAnswer = remainder;

    if ((x < 0) != (y < 0)) quotientAnswer = -quotientAnswer;
    if (x < 0) remainderAnswer = -remainderAnswer;

    cout << "Quotient decimal: " << quotientAnswer << endl;
    cout << "Quotient binary: ";
    printBinary32((unsigned int)quotientAnswer);
    cout << endl;

    cout << "Remainder decimal: " << remainderAnswer << endl;
    cout << "Remainder binary: ";
    printBinary32((unsigned int)remainderAnswer);
    cout << endl;

    return 0;
}
