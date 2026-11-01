// 2 hemjeest husnegtees mur buriin hamgiin baga elemtuudeer neg hemjeest husnegt uusne. dahvardaj oroogui elemntuudeer husnegt uusgene
#include <stdio.h>
int main(void) {
    int n, i, j, uniq, cnt;
    printf("n: ");
    scanf("%d", &n);
    double a[n][n], b[n], d[n];
    printf("%d x %d matrix:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        b[i] = a[i][0];
        for (j = 1; j < n; j++) {
            if (a[i][j] < b[i]) {
                b[i] = a[i][j];
            }
        }
    }
    printf("1 hemjeest array: ");
    for (i = 0; i < n; i++) printf("%g ", b[i]);
    printf("\n");
    uniq = 0;
    for (i = 0; i < n; i++) {
        cnt = 0;
        for (j = 0; j < n; j++) {
            if (b[j] == b[i]) {
                cnt++;
            }
        }
        if (cnt == 1) {
            d[uniq] = b[i];
            uniq++;
        }
    }
    printf("Davhardaagui array: ");
    if (uniq == 0) {
        printf("davhardaagui element baihgui");
    }
    for (i = 0; i < uniq; i++) printf("%g ", d[i]);
    printf("\n");
    return 0;
}
