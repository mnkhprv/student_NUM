#include <stdio.h>
#include <time.h>
int main(void) {
    int n, i, j, min;
    double k;
    clock_t ehlehTsag, duussanTsag;
    double ehlesen, duussan, urgeljilsen;
    scanf("%d", &n);
    double a[n];
    for (i = 0; i < n; i++) {
        scanf("%lf", &a[i]);
    }
    for (i = 0; i < n; i++) {
        printf("%g ", a[i]);
    }
    printf("\n");
    ehlehTsag = clock();
    for (i = 0; i < n - 1; i++) {
        min = i;
        j = i + 1;
        for (; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        k = a[i];
        a[i] = a[min];
        a[min] = k;
    }
    duussanTsag = clock();
    for (i = 0; i < n; i++) {
        printf("%g ", a[i]);
    }
    printf("\n");
    ehlesen = ehlehTsag * 1.0 / CLOCKS_PER_SEC;
    duussan = duussanTsag * 1.0 / CLOCKS_PER_SEC;
    urgeljilsen = (duussanTsag - ehlehTsag) * 1.0 / CLOCKS_PER_SEC;
    printf("Ehlesen tsag: %.6f\n", ehlesen);
    printf("Duussan tsag: %.6f\n", duussan);
    printf("Urgeljilsen tsag: %.6f\n", urgeljilsen);
    return 0;
}
