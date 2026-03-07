#include <iostream>
using namespace std;

int main(){
    
    int a=125;          // a-d 125iig onoov

    int *p = &a;        // int turliin p pointert a-iin haygiig onoov

    cout<<p << endl;    // p iin utga buyu a-iin haygiig hevlev

    cout<<*p << endl;   // p pointeriin  zaaj bui utga buyu a-iin utgiig hevlene

    p++;                // p pointeriig int hemjee buyu 4 byte(1-eer) nemegduulev

    cout<<p << endl;    // nemegduulsen utga buyu 4 byte iluu

    cout<<*p << endl;   // nemegduulsen haygandah utgiig hevlene
    return 0;
}
