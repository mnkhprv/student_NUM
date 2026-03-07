#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NO_OF_CHARS 256

int max(int a, int b) { return (a > b) ? a : b; }                       // hoyr toonii ihiin oloh

                                                                        // bad char heuristic husnegt uusgeh
void badCharHeuristic(char* str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
      badchar[i] = -1;                // buh temdegtuudiig -1 utgatai bolgoh

    for (int i = 0; i < size; i++)      // temdegt muriig suuliin temdegtuudiiig indexeer ni temdegleh
      badchar[(int)str[i]] = i;
}

int countWords(char* text, int index) {                                             // ugiin too tootsooloh 
    int count = 0;
    int inWord = false;
    int length = strlen(text);
    if (index > length) index = length;
    for (int i = 0; i < index; i++)
      if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') {
        inWord = false;
      }else if (!inWord) {
        count++;
        inWord = true;
      }
    return count;
}

void search(char* txt, char* pat) {                                     //boyer moore algorithmiig heregjuuleh
    int m = strlen(pat);
    int n = strlen(txt);

    int badchar[NO_OF_CHARS];                                          // badchar husnegt uusgeh
    badCharHeuristic(pat, m, badchar);

    int s = 0;                                                         // text deer guigeh index
    int foundCount = 0;                                                // duriig tooloh
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])                 // temdegt muriig tugsguluus ni ehlej shalgah
            j--;

        if (j < 0) {                             
          int wordIndex = countWords(txt, s) + 1;              // oldson ugiin too
            printf("\nOruulsan ugiin ehnii index: %d tus ugiin texted ezleh bair: %d", s, wordIndex);
                                                               // herev buh temdegt taarsan bol hevleh
            foundCount++;
            
                                                               // Daraagin bairlal ruu shiljih
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        }
        else {
            s += max(1, j - badchar[txt[s + j]]);        // bad char-iin durmiig ashiglaj guilgeh hemjeeg tootsooloh
        }
    }
    
    printf("\n\nNiit %d udaa oldloo.\n", foundCount);
}

int main() {
    char txt[1000], pat[1000];
    
    printf("Text oruulna uu: ");
    fgets(txt, sizeof(txt), stdin);
    txt[strcspn(txt, "\n")] = '\0';                      // shine muriig ustgah
    
    printf("Haih ded muriig oruulna uu: ");
    fgets(pat, sizeof(pat), stdin);
    pat[strcspn(pat, "\n")] = '\0';                     
    
    printf("\nText: \"%s\"\n", txt);
    printf("Haih ded mur: \"%s\"\n", pat);
    
    search(txt, pat);
    return 0;
}