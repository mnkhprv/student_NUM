#include <iostream>

using namespace std;

int main() {


    char *p1;           // Char turliin p1 pointer zarllaa

    int *p2;            // int ruliin p2 pointer zarllaa

    double *p3;         // DOUBLE  turliin p3 huvisagch zarlav
                        

    cout<<sizeof(p1)<<sizeof(p2)<<sizeof(p3) << endl; //хэд хэд гэсэн утга хэвлэж байна вэ? Яагаад?
    return 0;                                         // pointeriin hemjee 64bit OS-d 8 bite baidag tul 888 gej hevlene
}