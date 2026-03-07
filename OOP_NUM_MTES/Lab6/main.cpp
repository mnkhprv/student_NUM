#include "Student.h"
#include <iostream>
using namespace std;

// Нэрээр эрэмбэлэх функц (Bubble Sort)
void sortByName(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].after(arr[j + 1])) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Курсээр эрэмбэлэх функц (Bubble Sort)
void sortByCourse(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].greatThan(arr[j + 1])) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    cout << "Oyuutny too oruulna uu: ";
    int n;
    cin >> n;
    Student* students = new Student[n]; 
    for (int i = 0; i < n; i++) {
        cout << "\nOyuutny " << (i + 1) << " - r: \n";
        students[i].getData();
    }
    cout << "\nOyuutny medeelliig nereeer erembelne:\n";
    sortByName(students, n);
    cout << "\nNereer erembelsen oyuutny medeelluud:\n";
    for (int i = 0; i < n; i++) {
        students[i].print();
    }
    cout << "\nOyuutny medeelliig kurseer erembelne:\n";
    sortByCourse(students, n);
    cout << "\nKurseer erembelsen oyuutny medeelluud:\n";
    for (int i = 0; i < n; i++) {
        students[i].print();
    }
    cout << "\nТоо: " << students->getCount() << endl;

    return 0;
}