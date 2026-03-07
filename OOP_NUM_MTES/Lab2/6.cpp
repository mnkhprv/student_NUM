#include<iostream>
using namespace std;

void hayg_solih(int &too1, int& too2){
    int t = too1;
    too1 = too2;
    too2 = t;
}

int main(){

    int i = 0, j = 1;
    cout << "Solihoos umnu: i = " << i << ", j = " << j << endl;

    hayg_solih(i, j);

    cout << "Solisnii daraa: i = " << i << ", j = " << j << endl;
    
    return 0;
}