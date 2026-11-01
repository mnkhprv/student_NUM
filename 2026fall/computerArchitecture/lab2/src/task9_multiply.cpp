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
    bool negative = (x < 0) != (y < 0);

    unsigned int first = x < 0 ? -x : x;
    unsigned int second = y < 0 ? -y : y;
    unsigned int product = 0;

    while (second > 0) {
        if (second & 1) product = product + first;
        first = first << 1;
        second = second >> 1;
    }

    int answer;
    if (negative) answer = -product;
    else answer = product;

    cout << "Decimal result: " << answer << endl;
    cout << "Binary result: ";
    printBinary32((unsigned int)answer);
    cout << endl;

    return 0;
}
