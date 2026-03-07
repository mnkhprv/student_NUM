#ifndef CIRCLE_H
#define CIRCLE_H
#include "TwoDimensionalShape.h"
class Circle : public TwoDimensionalShape 
{
private:
    double radius; 
public:
    Circle(const string& n = "Circle", double cx = 0, double cy = 0, double r = 1);
    void setRadius(double r);
    double getRadius() const;
    double area() const override;
    double perimeter() const override;
    void display() const override;
};
#endif