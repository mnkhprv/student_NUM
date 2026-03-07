#include "circle.h"
#include <iostream>
#include <cmath>
using namespace std;
Circle::Circle(const string& n, double cx, double cy, double r)
    : TwoDimensionalShape(n, cx, cy), radius(r) {}
void Circle::setRadius(double r) {
    if (r > 0) {
        radius = r;
    }
}
double Circle::getRadius() const {
    return radius;
}
double Circle::area() const {
    return M_PI * radius * radius;
}
double Circle::perimeter() const {
    return 2 * M_PI * radius;
}
void Circle::display() const {
    cout << name << ": Төв=(" << getx1() << "," << gety1() << "), Радиус=" << getRadius() << endl;
    cout << "Талбай: " << area() << endl;
    cout << "Периметр: " << perimeter() << endl;
}