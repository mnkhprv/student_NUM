#ifndef TWODIMENSIONALSHAPE_H
#define TWODIMENSIONALSHAPE_H

#include "Shape.h"
#include <iostream>
#include <cmath>
using namespace std;

class TwoDimensionalShape : public Shape 
{
protected:
    double x1, y1;

public:
    TwoDimensionalShape(const string& n, double x = 0, double y = 0)
        : Shape(n), x1(x), y1(y) {}

    double getx1() const { return x1; }
    double gety1() const { return y1; }

    void setx1(double a) { x1 = a; }
    void sety1(double b) { y1 = b; }

    void setPosition(double a, double b) {
        if (!isfinite(a) || !isfinite(b)) {
            cout << "buruu too baina" << endl;
            return;
        }
        x1 = a;
        y1 = b;
    }
};

#endif
