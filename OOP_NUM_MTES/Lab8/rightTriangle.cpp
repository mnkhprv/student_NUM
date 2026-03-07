#include "rightTriangle.h"
#include <iostream>
#include <cmath>
using namespace std;

RightTriangle::RightTriangle(const string& n, double topX, double topY, double s)
    : TwoDimensionalShape(n, topX, topY), side(s)
{
    x2 = x1 - s / 2.0;
    y2 = y1 - s * sqrt(3) / 2.0;
    x3 = x1 + s / 2.0;
    y3 = y1 - s * sqrt(3) / 2.0; 
}

void RightTriangle::setSide(double s) {
    if (s > 0) {
        side = s;   
        x2 = x1 - s / 2.0;
        y2 = y1 - s * sqrt(3) / 2.0;
        x3 = x1 + s / 2.0;
        y3 = y1 - s * sqrt(3) / 2.0; 
    }
}
double RightTriangle::getSide() const {
    return side;
}
void RightTriangle::setA(double x, double y) { Ax = x; Ay = y; }
void RightTriangle::setB(double x, double y) { Bx = x; By = y; }
void RightTriangle::setC(double x, double y) { Cx = x; Cy = y; }
double RightTriangle::getAx() const { return Ax; }
double RightTriangle::getAy() const { return Ay; }
double RightTriangle::getBx() const { return Bx; }
double RightTriangle::getBy() const { return By; }
double RightTriangle::getCx() const { return Cx; }
double RightTriangle::getCy() const { return Cy; }
double RightTriangle::area() const {
    return (side * side * sqrt(3)) / 4.0;
}
double RightTriangle::perimeter() const {
    return side * 3.0;
}
void RightTriangle::display() const {
    cout << "Deed oroi: (" << getx1() << ", " << gety1() << ")" << endl;
    cout << "Taliin urt: " << getSide() << endl;
    cout << "Oroi:" << endl;
    cout << " A = (" << getAx() << ", " << getAy() << ")" << endl;
    cout << " B = (" << getBx() << ", " << getBy() << ")" << endl;
    cout << " C = (" << getCx() << ", " << getCy() << ")" << endl;
    cout << "Area: " << area() << endl;
    cout << "Perimeter: " << perimeter() << endl;
}