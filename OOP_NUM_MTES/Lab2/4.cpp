#include<iostream>

using namespace std;
int main(){

    int numbers[5];                 // 5 shirheg int elemttei massive zarlaj baina.

    int * p;                        // INT turliin p haygan huvisagch zarlav. 

    p = numbers; *p = 10;           // p numbers[0] ruu zaana. *p = 10 -> numbers[0] = 10;
    p++; *p = 20;                   // p numbers[1] ruu zaana. *p = 20

    p = &numbers[2]; *p = 30;       // p numbers[2] ruu zaana. *p = 30;

    p = numbers + 3; *p = 40;       // p numbers[3], *p = 40

    p = numbers; *(p+4) = 50;       // p numbers[0], *(p + 4) -> numbers[4]; numbers[4] = 50

    for (int n=0; n<5; n++)

    cout << numbers[n] << ", ";     // massive-iin buh elemntiig hevlene.

    return 0;

}
