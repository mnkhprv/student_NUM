#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H
#include "TwoDimensionalShape.h"

class RightTriangle : public TwoDimensionalShape {
private:
    double side; // тэнцүү талуудын урт
    double x2, y2; // зүүн доод
    double x3, y3; // баруун доод

public:
    RightTriangle(const string& n = "RightTriangle", double topX = 0, double topY = 0, double s = 1) 
    : TwoDimensionalShape(n, topX, topY), side(s){}
    
    void setSide(double s);
    double getSide() const;
    
    void setx2(double x);
    void sety2(double y);
    void setx3(double x);
    void sety3(double y);
    
    double gety3() const;  
    double getx2() const; 
    double getx3() const;  
    double gety2() const;
        
    double area() const override;
    double perimeter() const override;
    void display() const override;
};

#endif