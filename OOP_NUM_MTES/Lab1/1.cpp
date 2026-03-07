#include<iostream>
#define MAX3(a, b, c) (((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c))))


using namespace std;

int main() {

    int a = MAX3(10, 3, 11);

    cout <<  "Max: " << a << endl;

    int b = MAX3(10+2, 3+9, 11+2);

    cout <<  "Max: " << b << endl;



    return 0;
}