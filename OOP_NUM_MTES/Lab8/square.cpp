#include "square.h"
#include <iostream>
using namespace std;

Square::Square(const string& n, double topLeftX, double topLeftY, double s)
    : TwoDimensionalShape(n, topLeftX, topLeftY), side(s)
{
    Ax = x1;
    Ay = y1;
    Bx = x1 + s;
    By = y1;
    Cx = x1 + s;
    Cy = y1 - s;
    Dx = x1;
    Dy = y1 - s;
}

void Square::setSide(double s) {
    if (s > 0) {
        side = s;
        Ax = x1;        Ay = y1;
        Bx = x1 + s;    By = y1;
        Cx = x1 + s;    Cy = y1 - s;
        Dx = x1;        Dy = y1 - s;
    }
}

double Square::getSide() const {
    return side;
}

void Square::setA(double x, double y) { Ax = x; Ay = y; }
void Square::setB(double x, double y) { Bx = x; By = y; }
void Square::setC(double x, double y) { Cx = x; Cy = y; }
void Square::setD(double x, double y) { Dx = x; Dy = y; }
double Square::getAx() const { return Ax; }
double Square::getAy() const { return Ay; }
double Square::getBx() const { return Bx; }
double Square::getBy() const { return By; }
double Square::getCx() const { return Cx; }
double Square::getCy() const { return Cy; }
double Square::getDx() const { return Dx; }
double Square::getDy() const { return Dy; }
double Square::area() const {
    return side * side;
}
double Square::perimeter() const {
    return 4 * side;
}
void Square::display() const {
    cout << "Zuun deed: (" << getx1() << ", " << gety1() << ")" << endl;
    cout << "Taliin urt: " << getSide() << endl;
    cout << "Oroi:" << endl;
    cout << " A = (" << getAx() << ", " << getAy() << ")" << endl;
    cout << " B = (" << getBx() << ", " << getBy() << ")" << endl;
    cout << " C = (" << getCx() << ", " << getCy() << ")" << endl;
    cout << " D = (" << getDx() << ", " << getDy() << ")" << endl;
    cout << "Area: " << area() << endl;
    cout << "Perimeter: " << perimeter() << endl;
}

