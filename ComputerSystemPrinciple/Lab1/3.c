# include <stdio.h>

typedef struct {
    int a [2];
    double d;
} struct_t ;

double fun (int i) {
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824;
    return s.d;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        if(i < 0 || i >= 2){
            printf("i = %d uyd aldaa\n", i);

        }else{
            printf("i = %d uyf %2f\n", i, fun(i));
        }
    }
    
    

    return 0;
}   