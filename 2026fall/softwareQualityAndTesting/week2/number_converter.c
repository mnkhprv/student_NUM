#include <stdio.h>

int main(void) {
    int songolt;

    printf("1. Aravtiin toog hoyort ruu horvuuleh\n");
    printf("2. Hoyortiin toog aravt ruu horvuuleh\n");
    printf("Songoltoo oruulna uu: ");

    if (scanf("%d", &songolt) != 1 || (songolt != 1 && songolt != 2)) {
        printf("Buruu songolt.\n");
        return 1;
    }

    if (songolt == 1) {
        char aravtiinToo[80];
        char bituud[64];
        unsigned long long buhelHeseg = 0;
        double butarhaiHeseg = 0, aravtiinOron = 0.1;
        int bitiinToo = 0, sorog = 0, tsegOrson = 0, tsifrOrson = 0, i;

        printf("Aravtiin too: ");
        scanf("%79s", aravtiinToo);

        if (aravtiinToo[0] == '-') {
            sorog = 1;
        }

        /* Tsegnees omnoh ba daraah tsifruudiig tusad ni tootsoolno. */
        for (i = sorog; aravtiinToo[i] != '\0'; i++) {
            if (aravtiinToo[i] == '.' && tsegOrson == 0) {
                tsegOrson = 1;
                continue;
            }

            if (aravtiinToo[i] < '0' || aravtiinToo[i] > '9') {
                printf("Buruu aravtiin too.\n");
                return 1;
            }

            tsifrOrson = 1;
            if (tsegOrson == 0) {
                buhelHeseg = buhelHeseg * 10 + aravtiinToo[i] - '0';
            } else {
                butarhaiHeseg += (aravtiinToo[i] - '0') * aravtiinOron;
                aravtiinOron /= 10;
            }
        }

        if (!tsifrOrson) {
            printf("Buruu aravtiin too.\n");
            return 1;
        }

        /* Buhlel hesgiig 2-t huvaaj, uldegdliig hadgalna. */
        if (buhelHeseg == 0) {
            bituud[bitiinToo++] = 0;
        }

        while (buhelHeseg > 0) {
            bituud[bitiinToo++] = buhelHeseg % 2;
            buhelHeseg /= 2;
        }

        printf("Hoyortiin too: ");
        if (sorog) {
            printf("-");
        }

        for (i = bitiinToo - 1; i >= 0; i--) {
            printf("%d", bituud[i]);
        }

        /* Butarhai hesgiig 2-oor urjuulj, 16 oron hurtel gargana. */
        if (butarhaiHeseg > 0.000000000001) {
            printf(".");

            for (i = 0; i < 16 && butarhaiHeseg > 0.000000000001; i++) {
                butarhaiHeseg *= 2;
                if (butarhaiHeseg >= 1) {
                    printf("1");
                    butarhaiHeseg -= 1;
                } else {
                    printf("0");
                }
            }
        }

        printf("\n");
    } else {
        char hoyortiinToo[80];
        int i, sorog = 0, tsegOrson = 0, tsifrOrson = 0;
        double urDun = 0, hoyortiinOron = 0.5;

        printf("Hoyortiin too: ");
        scanf("%79s", hoyortiinToo);

        if (hoyortiinToo[0] == '-') {
            sorog = 1;
        }

        /* Neg davtaltaar shalgaj, aravtiin utgiig tootsoolno. */
        for (i = sorog; hoyortiinToo[i] != '\0'; i++) {
            if (hoyortiinToo[i] == '.' && tsegOrson == 0) {
                tsegOrson = 1;
                continue;
            }

            if (hoyortiinToo[i] != '0' && hoyortiinToo[i] != '1') {
                printf("Buruu hoyortiin too.\n");
                return 1;
            }

            tsifrOrson = 1;
            if (tsegOrson == 0) {
                urDun = urDun * 2 + hoyortiinToo[i] - '0';
            } else {
                if (hoyortiinToo[i] == '1') {
                    urDun += hoyortiinOron;
                }
                hoyortiinOron /= 2;
            }
        }

        if (!tsifrOrson) {
            printf("Buruu hoyortiin too.\n");
            return 1;
        }

        if (sorog) {
            urDun = -urDun;
        }

        printf("Aravtiin too: %.12g\n", urDun);
    }

    return 0;
}
