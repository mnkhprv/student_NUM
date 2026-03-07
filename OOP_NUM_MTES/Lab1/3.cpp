#include <iostream>
using namespace std;

inline int tegsh(int a[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++){
        if (a[i] % 2 == 0)
        {
            s++;
        }
    }
    return s;
}

int main() {

    int a[] = {
        1, 2, 3, 4, 3, 2, 5, 5, 6
    };

    int n = 9;
    int hariu = tegsh(a, n);

    cout << hariu << endl;
    return 0;
}

// 3. Өгөгдсөн хүснэгтийн тэгш элементүүдийн тоог олох дотоод функц бич.

