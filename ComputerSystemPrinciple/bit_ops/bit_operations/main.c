#include "ops.h"
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
#include <string.h>
#include <stdio.h>
char check_mark[] = {0xE2, 0x9C, 0x85, 0x0};
int main()
{
        FILE *fin = fopen("test.in", "r");
        if (fin == NULL) {
                fprintf(stderr, "test.in файл олдсонгүй\n");
                return -1;
        }
        int T;
        fscanf(fin, "%d", &T);
        printf("p1() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, corr, out;
                fscanf(fin, "%d", &n);
                fscanf(fin, "%d", &corr);
                out = p1(n);
                if (out != corr) {
                        fprintf(stderr, "p1 функц %d утга дээр алдсан", n);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p2() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, corr, out;
                fscanf(fin, "%d", &n);
                fscanf(fin, "%d", &corr);
                out = p2(n);
                if (out != corr) {
                        fprintf(stderr, "p2 функц %d утга дээр алдсан", n);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p3() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, k, corr, out;
                fscanf(fin, "%d%d", &n, &k);
                fscanf(fin, "%d", &corr);
                out = p3(n, k);
                if (out != corr) {
                        fprintf(stderr, "p3 функц n=%d, k=%d утга дээр алдсан", n, k);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p4() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, k, corr, out;
                fscanf(fin, "%d%d", &n, &k);
                fscanf(fin, "%d", &corr);
                out = p4(n, k);
                if (out != corr) {
                        fprintf(stderr, "p4 функц n=%d, k=%d утга дээр алдсан", n, k);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p5() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, k, corr, out;
                fscanf(fin, "%d%d", &n, &k);
                fscanf(fin, "%d", &corr);
                out = p5(n, k);
                if (out != corr) {
                        fprintf(stderr, "p5 функц n=%d, k=%d утга дээр алдсан", n, k);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p6() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, corr, out;
                fscanf(fin, "%d", &n);
                fscanf(fin, "%d", &corr);
                out = p6(n);
                if (out != corr) {
                        fprintf(stderr, "p6 функц %d утга дээр алдсан", n);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p7() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, corr, out;
                fscanf(fin, "%d", &n);
                fscanf(fin, "%d", &corr);
                out = p7(n);
                if (out != corr) {
                        fprintf(stderr, "p7 функц %d утга дээр алдсан", n);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p8() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, corr, out;
                fscanf(fin, "%d", &n);
                fscanf(fin, "%d", &corr);
                out = p8(n);
                if (out != corr) {
                        fprintf(stderr, "p8 функц %d утга дээр алдсан", n);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p9() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, corr, out;
                fscanf(fin, "%d", &n);
                fscanf(fin, "%d", &corr);
                out = p9(n);
                if (out != corr) {
                        fprintf(stderr, "p9 функц %d утга дээр алдсан", n);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p10() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, corr, out;
                fscanf(fin, "%d", &n);
                fscanf(fin, "%d", &corr);
                out = p10(n);
                if (out != corr) {
                        fprintf(stderr, "p10 функц %d утга дээр алдсан", n);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        printf("p11() функцийг шалгаж байна: ");
        fflush(stdout);
        int fd_out = open("tmp.out", O_CREAT|O_WRONLY|O_TRUNC);
        if (fd_out == -1) {
                fprintf(stderr, "Уг хавтаст бичих эрхгүй байна.\n");
                return -1;
        }
        int saved_fd = dup(1);
        dup2(fd_out, 1);
        for (int _t = 0; _t < T; _t++) {
                int n;
                fscanf(fin, "%d", &n);
                p11(n);
        }
        fflush(stdout);
        dup2(saved_fd, 1);
        close(fd_out);
        close(saved_fd);
        FILE *f1 = fopen("test.out", "r");
        FILE *f2 = fopen("tmp.out", "r");
        if (f1 == NULL) {
                fprintf(stderr, "test.out файл олдсонгүй\n");
                return -1;
        }
        if (f2 == NULL) {
                fprintf(stderr, "tmp.out файл олдсонгүй\n");
                return -1;
        }

        char s1[50], s2[50];
        while (!feof(f1)) {
                fgets(s1, 50, f1);
                fgets(s2, 50, f2);
                int len = strlen(s1) - 1;
                while (s1[len] == ' ' || s1[len] == '\n') len--;
                s1[len+1] = 0;
                len = strlen(s2) - 1;
                while (s2[len] == ' ' || s2[len] == '\n') len--;
                s2[len+1] = 0;
                if (strcmp(s1, s2) != 0) {
                        fprintf(stderr, "p11 функц алдаатай");
                        return -1;
                }
        }

        printf("%s\n", check_mark);
        printf("p12() функцийг шалгаж байна: ");
        fflush(stdout);
        for (int _t = 0; _t < T; _t++) {
                int n, k, corr, out;
                fscanf(fin, "%d%d", &n, &k);
                fscanf(fin, "%d", &corr);
                out = p12(n, k);
                if (out != corr) {
                        fprintf(stderr, "p12 функц n=%d, k=%d утга дээр алдсан", n, k);
                        return -1;
                }
        }
        printf("%s\n", check_mark);
        return 0;
}
