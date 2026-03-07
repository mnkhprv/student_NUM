#include <stdio.h>
#include <string.h>

void search(char pat[], char txt[], int q)                          // rabin karp herejuuleh algorithm
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;                                                      // duriin hash utga
    int t = 0;                                                      // textiin hash utga
    int h = 1;
    int d = 256;     
    int found = 0;                                                // ascii 0-255
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;                                            // h iin utga "pow(d, M-1)%q"

    for (i = 0; i < M; i++) {                                     // dur bolon ehnii hash utgiig tootsooloh
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++) {                                  
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M)
            printf("\nOruulsan ugiin ehnii index: %d", i);
            found = 1;
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    if (!found) {
        printf("dur textnd baihgui\n");
    }
}

int main() {
    char txt[1000000], pat[1000000];
    
    printf("Text oruulna uu: ");
    fgets(txt, sizeof(txt), stdin);
    txt[strcspn(txt, "\n")] = '\0';                      
    
    printf("Haih ded muriig oruulna uu: ");
    fgets(pat, sizeof(pat), stdin);
    pat[strcspn(pat, "\n")] = '\0';                     
    
    printf("\nText: \"%s\"\n", txt);
    printf("Haih ded mur: \"%s\"\n", pat);
    
    int q = 101;
    search(pat, txt, q);
    return 0;
}