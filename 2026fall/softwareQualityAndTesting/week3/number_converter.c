#include <stdio.h>
#include <time.h>

int main(void) {
    int n;              /* elementiin too */
    double a[100];      /* 10-tiin toonuud */
    char b[8600];       /* 2-tiin dursleluud daraalan, '\0'-oor tusgaarlagdana */
    int c[100];         /* 2-tiin dursleld baih 1-uudiin too */
    int i, j, k;
    int bairshil = 0;        /* b husnegtend bichih bairshil */
    int hamgiinIhIndex = 0;
    clock_t ehlehTsag, duussanTsag;
    double ehlesen, duussan, urgeljilsen;

    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        /* surug too ashiglahgui, buhel heseg ni husnegtend bagtah yostoi */
        if (scanf("%lf", &a[i]) != 1 || a[i] < 0.0 || a[i] >= 1000000000000000000.0) {
            return 1;
        }
    }

    ehlehTsag = clock();   /* oroltiin daraa, bodolt ehlehed */

    for (i = 0; i < n; i++) {
        double uldegdel = a[i];   /* uldej bui heseg */
        double p = 1.0;         /* 2-iin zereg */
        int bit;

        c[i] = 0;

        /* toonoos bagagui hamgiin ih 2-iin zeregiig oloh */
        while (p * 2.0 <= uldegdel) {
            p = p * 2.0;
        }

        /* buhel heseg: p >= 1 baih hurtel */
        while (p >= 1.0) {
            if (uldegdel >= p) {
                bit = 1;
                uldegdel = uldegdel - p;
            } else {
                bit = 0;
            }
            b[bairshil] = '0' + bit;
            bairshil++;
            c[i] += bit;
            p = p / 2.0;
        }

        /* butarhai heseg: p ni 0.5, 0.25, ... bolj urgeljilne */
        if (uldegdel > 0.0) {
            b[bairshil] = '.';
            bairshil++;
            for (j = 0; j < 20 && uldegdel > 0.0; j++) {
                if (uldegdel >= p) {
                    bit = 1;
                    uldegdel = uldegdel - p;
                } else {
                    bit = 0;
                }
                b[bairshil] = '0' + bit;
                bairshil++;
                c[i] += bit;
                p = p / 2.0;
            }
        }

        b[bairshil] = '\0';   /* element burnii tugsgul */
        bairshil++;

        if (c[i] > c[hamgiinIhIndex]) {
            hamgiinIhIndex = i;
        }
    }

    duussanTsag = clock(); /* bodolt duussan, garaltiin umnu */

    /* 1-r mor. Husnegtiin elementuud */
    for (i = 0; i < n; i++) {
        printf("%s%0.5f", i == 0 ? "" : " ", a[i]);
    }
    printf("\n");

    /* 2-r mor. Element buriin hoyortiin durslel */
    k = 0;
    for (i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        while (b[k] != '\0') {
            printf("%c", b[k]);
            k++;
        }
        k++;
    }
    printf("\n");

    /* 3-r mor. Dursleld dah 1-uudiin too */
    for (i = 0; i < n; i++) {
        printf("%s%d", i == 0 ? "" : " ", c[i]);
    }
    printf("\n");

    /* 4-r mor. Hamgiin olon 1-tei element */
    printf("%0.5f\n", a[hamgiinIhIndex]);

    ehlesen = ehlehTsag * 1.0 / CLOCKS_PER_SEC;
    duussan = duussanTsag * 1.0 / CLOCKS_PER_SEC;
    urgeljilsen = (duussanTsag - ehlehTsag) * 1.0 / CLOCKS_PER_SEC;

    printf("Ehlesen tsag: %.6f\n", ehlesen);
    printf("Duussan tsag: %.6f\n", duussan);
    printf("Urgeljilsen tsag: %.6f\n", urgeljilsen);

    return 0;
}
