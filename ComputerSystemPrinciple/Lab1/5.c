#include <stdio.h>
int main() {


	int n, m;
    scanf("%d %d", &n, &m);
	int a[100][100];

	for(int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	int tegsh = -1, sondgoi = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++){
			if(a[i][j] % 2 == 0){
				if(tegsh == -1 || a[i][j] > tegsh){
					tegsh = a[i][j];
				}

			}else{
				if(sondgoi == -1 || a[i][j] > sondgoi){
					sondgoi = a[i][j];
				}
			}
		}
	}
	if(tegsh == -1){
		printf("tegsh too baihgui\n");
	}else{
		printf("Hamgiin ih tesgh too: %d\n", tegsh);

	}
	if(sondgoi == -1){
        printf("sondgoi too baihgui\n");
	}else{
		printf("Hamgiin ih sondgoi too: %d\n", sondgoi);
	}

	return 0;
}
