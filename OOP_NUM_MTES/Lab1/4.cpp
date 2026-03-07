#include <iostream>
using namespace std;
inline float sondgoi(int n, int a[]) {
    float s = 0;
    float k = 0;
    for (int i = 0; i < n; i++){
        if(a[i] % 2 == 1){
            s += a[i];
            k++;
        }
    }
    return  s / k;
}


int main() {
    int a[] = {
        1, 2, 1, 4, 1, 2, 1, 1, 3, 1
    };

    int n = 10;
    float hariu = sondgoi(n, a);

    cout << hariu << endl;
    return 0;
}