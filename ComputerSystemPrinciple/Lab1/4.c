#include <stdio.h>

int main(){
	
	int n, m;

	scanf("%d", &n);
	scanf("%d", &m);
	int a[100][100];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	
	int mur = 0, bag = 0;
	
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mur += a[i][j];
            bag += a[j][i];
		}
		printf("%d-r muriin niilber:%d\n", i+1, mur);
        printf("%d-r baganiin niilber:%d\n", i+1, bag);
        bag = 0;
        mur = 0;
	}


	return 0;

}

// 4. N × M õýìæýýòýé õ³ñíýãòèéã ãàðààñ àâ÷ ì°ð á³ðèéí óòãóóäûí íèéëáýð, áàãàíà á³ðèéí
// óòãóóäûí íèéëáýðèéã õýâëýí õàðóóë.
