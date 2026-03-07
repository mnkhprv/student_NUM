// main.cpp - Simple demo for your Matrix class
#include "matrice.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=== Creating matrices ===\n";
    Matrix A(2, 3);
    Matrix B(2, 3);

    // Fill A
    A.setValue(0, 0, 1); A.setValue(0, 1, 2); A.setValue(0, 2, 3);
    A.setValue(1, 0, 4); A.setValue(1, 1, 5); A.setValue(1, 2, 6);

    // Fill B
    B.setValue(0, 0, 10); B.setValue(0, 1, 20); B.setValue(0, 2, 30);
    B.setValue(1, 0, 40); B.setValue(1, 1, 50); B.setValue(1, 2, 60);

    cout << "Matrix A:\n"; A.print();
    cout << "Matrix B:\n"; B.print();

    cout << "\n=== A + B ===\n";
    (A + B).print();

    cout << "\n=== A - B ===\n";
    (A - B).print();

    cout << "\n=== A + 5 ===\n";
    (A + 5.0f).print();

    cout << "\n=== Transpose of A ===\n";
    A.hurvuuleh().print();

    cout << "\n=== Multiply (need 3x2 * 2x3) ===\n";
    Matrix C(3, 2);
    C.setValue(0,0,1); C.setValue(0,1,2);
    C.setValue(1,0,3); C.setValue(1,1,4);
    C.setValue(2,0,5); C.setValue(2,1,6);

    Matrix D(2, 3);
    D.setValue(0,0,7); D.setValue(0,1,8); D.setValue(0,2,9);
    D.setValue(1,0,10); D.setValue(1,1,11); D.setValue(1,2,12);

    cout << "C (3x2):\n"; C.print();
    cout << "D (2x3):\n"; D.print();
    cout << "C * D:\n"; (C * D).print();

    cout << "\n=== Increment A ===\n";
    ++A;
    A.print();

    cout << "\n=== Resize A to 4x4 (adds zeros) ===\n";
    A.setR(4);
    A.setC(4);
    A.print();

    cout << "\nDone!\n";
    return 0;
}