#include <stdio.h>
#include<math.h>

long long bin = 0;

void def(int too){
    int ihzereg = 0;
    while(pow(2, ihzereg) <= too){
        ihzereg++;
    }
    ihzereg--;

    bin += pow(10, ihzereg);
    too = too - pow(2, ihzereg);

    while(too > 0){
        def(too);
        return;
    }
}
int main() {

    int too;
    scanf("%d", &too);

    def(too);
    
    printf("%lld\n", bin);
    
    return 0;
}