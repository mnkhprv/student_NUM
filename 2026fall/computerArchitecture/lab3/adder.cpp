#include <iostream>

void halfAdder(bool A, bool B, bool &C, bool &S) {
    C = A & B;
    S = (A & !B) | (!A & B);
}

void fullAdder(bool A, bool B, bool Cin, bool &Cout, bool &S) {
    bool C1, S1;
    bool C2, S2;

    halfAdder(A, B, C1, S1);
    halfAdder(S1, Cin, C2, S2);

    Cout = C1 | C2;
    S = S2;
}

int main() {
    bool C, S;

    std::cout << "Half adder (A B C S)\n";
    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            halfAdder(a, b, C, S);
            std::cout << a << " " << b << " " << C << " " << S << "\n";
        }
    }

    std::cout << "\nFull adder (A B Cin Cout S)\n";
    for (int a = 0; a <= 1; a++) {
        for (int b = 0; b <= 1; b++) {
            for (int cin = 0; cin <= 1; cin++) {
                bool Cout;
                fullAdder(a, b, cin, Cout, S);
                std::cout << a << " " << b << " " << cin << " "
                          << Cout << " " << S << "\n";
            }
        }
    }

    return 0;
}
