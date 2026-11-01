#include <stdio.h>
#include <time.h>
int main(void) {
    int n, i, j, m, min;
    double k, x;
    scanf("%d", &n);
    double a[n];
    for (i = 0; i < n; i++) scanf("%lf", &a[i]);
    scanf("%lf", &x);
    for (i = 0; i < n; i++) printf("%g ", a[i]);
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i; j < n; j++) if (a[j] < a[min]) min = j;
        k = a[i]; a[i] = a[min]; a[min] = k;
    }
    printf("\n");
    for (i = 0; i < n; i++) printf("%g ", a[i]);
    clock_t t = clock();
    i = 0;
    j = n - 1;
    while (i < j) {
        m = (i + j) / 2;
        if (a[m] == x) break;
        if (a[m] < x) i = m + 1;
        else j = m - 1;
    }

    if (i == j) {m = i;};
    if (a[m] != x) printf("\nBaikhgui\n");
    else printf("\nDugaar: %d\n", m);
    printf("Tsag: %.6f\n", (clock() - t) * 1.0 / CLOCKS_PER_SEC);
    return 0;
}
