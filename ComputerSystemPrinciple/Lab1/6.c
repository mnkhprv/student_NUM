#include<stdio.h>

struct EngiinButarxai {
    int d, n; // d - xurtver
              // n - xuviar
};
typedef struct EngiinButarxai EngiinButarxai ;
/*
Nemex uildel
*/
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

EngiinButarxai add( EngiinButarxai a, EngiinButarxai b){
	EngiinButarxai har;

    if (a.n == 0 || b.n == 0){
        printf("Aldaa! huvaari 0 bolomjgui utga uur utga oruul!\n");
        har.n = 1;
        har.d = 0;
        return har;
    }
    har.n = a.n * b.n;
    har.d = a.d * b.n + b.d * a.n;
    int huvaagch = gcd(har.d, har.n);
    har.n /=huvaagch;
    har.d /= huvaagch;
    return har;
} ;
/*
Xasax uildel
*/
EngiinButarxai sub( EngiinButarxai a, EngiinButarxai b){
    EngiinButarxai har;
    if (a.n == 0 || b.n == 0){
        printf("Aldaa! huvaari 0 bolomjgui utga uur utga oruul!");
        har.n = 1;
        har.d = 0;
        return har;
    }
    har.n = a.n * b.n;
    har.d = a.d * b.n - b.d * a.n;
    int huvaagch = gcd(har.d, har.n);
    har.n /=huvaagch;
    har.d /= huvaagch;
    return har;
} ;
/*
Urjix uildel
*/
EngiinButarxai mult ( EngiinButarxai a, EngiinButarxai b){
    EngiinButarxai har;
    if (a.n == 0 || b.n == 0){
        printf("Aldaa! huvaari 0 bolomjgui utga uur utga oruul!");
        har.n = 1;
        har.d = 0;
        return har;
    }

    har.n = a.n * b.n;
    har.d = a.d * b.d;
    int huvaagch = gcd(har.d, har.n);
    har.n /=huvaagch;
    har.d /= huvaagch;
    return har;

} ;
/*
Xuvaax uildel
*/
EngiinButarxai div( EngiinButarxai a, EngiinButarxai b) {
    EngiinButarxai har;
    if (a.n == 0 || b.n == 0){
        printf("Aldaa! huvaari 0 bolomjgui utga uur utga oruul!");
        har.n = 1;
        har.d = 0;
        return har;
    }

    har.n = a.n * b.d;
    har.d = a.d * b.n;
    int huvaagch = gcd(har.d, har.n);
    har.n /=huvaagch;
    har.d /= huvaagch;
    return har;

};
/*
Hewlex uildel
*/
void print ( EngiinButarxai a){
    printf("%d/%d\n", a.d, a.n);
} ;

int main ()
{
    // funtsuudaa shalga
    EngiinButarxai a = {2, 3}, b = {5, 6};
    printf("a + b: ");
    print(add(a, b));

    printf("a - b ");
    print(sub(a, b));

    printf("a * b: ");
    print(mult(a, b));

    printf("a / b: ");
    print(div(a, b));

    return 0;
}
