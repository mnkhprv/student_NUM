#include<iostream>
using namespace std;

int def(int n, int a[]){
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
        }
    }
    return max;
}

int fed(int n, int a[]){
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (min > a[i]) {
            min = a[i];
        }
    }
    return min;
}

int main() {

    int a[] = {
        1, 2, 3, 4, 3, 2, 5, 5, 6
    };

    int n = 9;

    int hariu = def(n, a);
    int hariu1 = fed(n, a);

    cout << hariu << endl;
    cout << hariu1 << endl;

    return 0;
}