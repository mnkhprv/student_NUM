#include <iostream>
using namespace std;

inline int orontoo(int n){
        int s = 0;
        while(n > 0){
            s++;
            n /= 10;
        }
        return s;
    }

inline void tsifr(int n, int a[]) {
    int len = orontoo(n);
    for (int i = len - 1; i >= 0; i--) {
        a[i] = n % 10;
        n /= 10;
    }
}

int main(){

    int n = 56789;
    int a[10];
    int len = orontoo(n);
    tsifr(n, a);
    cout << "Orongiin too: " << orontoo(n) << endl;
    cout << "Цифрүүд: ";
    for (int i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;



    return 0;
}