#ifndef SHAPE_H
#define SHAPE_H
#include <string>
using namespace std;
class Shape 
{
  protected: 
    string name;
  public:
    Shape(const string& n = "Shape") : name(n){}
    virtual ~Shape() = default;
    void setName(const string& n){name = n;}
    string getName() const { return name;}
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void display() const = 0;
};


#endif