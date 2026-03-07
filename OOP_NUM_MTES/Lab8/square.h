    #ifndef SQUARE_H
    #define SQUARE_H
    #include "TwoDimensionalShape.h"
    class Square : public TwoDimensionalShape {
    private:
        double side;
        double Ax, Ay;
        double Bx, By;
        double Cx, Cy;
        double Dx, Dy;
    public:
        Square(const string& n = "Square", double topLeftX = 0, double topLeftY = 0, double s = 1);
        void setSide(double s);
        double getSide() const;

        void setA(double x, double y);
        void setB(double x, double y);
        void setC(double x, double y);
        void setD(double x, double y);
        
        double getAx() const;  double getAy() const;
        double getBx() const;  double getBy() const;
        double getCx() const;  double getCy() const;
        double getDx() const;  double getDy() const;    

        double area() const override;
        double perimeter() const override;
        void display() const override;
    };

    #endif