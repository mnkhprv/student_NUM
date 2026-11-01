#include <stdio.h>
int main(void) {
    char t[1000] = "", s[1000] = "";
    int shift[256];
    int tlen, slen, i, j, cnt;
    printf("T: ");
    scanf("%999[^\n]", t);
    getchar();
    printf("S: ");
    scanf("%999[^\n]", s);
    tlen = 0;
    while (t[tlen] != '\0') tlen++;
    slen = 0;
    while (s[slen] != '\0') slen++;
    printf("%s\n", t);
    printf("%s\n", s);
    for (i = 0; i < 256; i++) shift[i] = slen;
    for (j = 0; j < slen - 1; j++) shift[s[j] + 128] = slen - 1 - j;
    cnt = 0;
    i = 0;
    while (slen > 0 && i + slen <= tlen) {
        j = slen - 1;
        while (j >= 0 && t[i + j] == s[j]) j--;
        if (j < 0) {
            printf("%d ", i);
            cnt++;
        }
        i += shift[t[i + slen - 1] + 128];
    }
    printf("\n");
    printf("%d udaa baina.\n", cnt);
    return 0;
}
