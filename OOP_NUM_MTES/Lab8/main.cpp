#include <iostream>
#include <vector>
#include "circle.h"
#include "square.h"
#include "rightTriangle.h"
using namespace std;

void sortByArea(vector<TwoDimensionalShape*>& v) {
    int n = v.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (v[j]->area() > v[j+1]->area())
                swap(v[j], v[j+1]);
}

int main() {
    vector<TwoDimensionalShape*> shapes;

    shapes.push_back(new Circle("Тойрог1", 0, 0, 5));
    shapes.push_back(new Circle("Тойрог2", 10, 10, 2));
    shapes.push_back(new Square("Дөрвөлжин1", 0, 10, 6));
    shapes.push_back(new Square("Дөрвөлжин2", -5, -5, 10));
    shapes.push_back(new RightTriangle("Гурвалжин1", 0, 0, 8));
    shapes.push_back(new RightTriangle("Гурвалжин2", 15, 15, 4));

    sortByArea(shapes);

    cout << "=== Талбайгаар эрэмбэлсэн жагсаалт (Bubble Sort) ===\n\n";
    for (auto* s : shapes) {
        s->display();
        cout << "------------------------\n";
    }

    for (auto* s : shapes) delete s;
    return 0;
}