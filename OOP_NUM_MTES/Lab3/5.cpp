#include <iostream>
#include <cstring>
#include <limits>
using namespace std;

class ajilchin {
private:
    int dugaar;
    char ner[20];
    char alba[10];
    float tsag;
    float zahirliinTsalin() {
        if(strcmp(alba, "zahiral") == 0){
            int uTsalin, une = 5000;
            uTsalin = tsag * une;
            return uTsalin + 200000;
        }
        return 0;
    }

public:
    ajilchin(){
        
        dugaar = 0;
        strcpy(ner, "");
        strcpy(alba, "");
        tsag = 0;
    }
    void getData(){
        int i; char n[20], a[10]; float t;
        setDugaar(i);
        setNer(n);
        setAlba(a);
        setTsag(t);
    }
    void setNer(char n[]){
        cout << "Ner: ";
        cin >> n;
        if(strlen(n) > 20 || cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "ner 20 temdegtees burdeh ystoi!" << endl;
            setNer(n);
        }else{
            strcpy(ner, n);
        }
    };
    char* getNer() {return ner;}
    void setDugaar(int d){
        int minD = 0, maxD = 999;
        cout << "\nDugaar oruulna uu (" << minD << "-" << maxD << "): ";
        cin >> d;
        if(cin.fail() || d < minD || d > maxD){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "0 - 999 hoorond toon utga oruulna uu";
            setDugaar(d);
        }else{
            dugaar = d;
        }
    };
    int getDugaar() {return dugaar;}
    void setAlba(char n[]){
        cout << "Alba: ";
        cin >> n;
        if(strlen(n) > 10 || cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "alba 10 temdegtees burdeh ystoi!" << endl;
            setAlba(n);
        }else{
            strcpy(alba, n);
        }
    };
    char* getAlba() {return alba;}
    void setTsag(float t){
        cout << "Tsag: ";
        cin >> t;
        if (t < 0 || t > 24 || cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "1-23 hoorond tsag zuv oruulna uu!" << endl;
            setTsag(t);
        }else{
            tsag = t;
        }
    };
    float getTsag() {return tsag;}

    float tsalinBodoh() {
        if(strcmp(alba, "zahiral") == 0){
            return zahirliinTsalin();
        }
        float une = 5000;
        float tsalin = tsag * une;
        return tsalin;
    }
    void showData(){
        cout << "\nDugaar: " << getDugaar();
        cout << "\nNer: " << getNer();
        cout << "\nAlba: " << getAlba();
        cout << "\nTsag: " << getTsag();
        cout << "\nTsalin: " << tsalinBodoh() << "$";
        cout << endl;
    }
    bool tsagNemegduuleh(float nemelt){
        if (nemelt <= 24 && nemelt >= 0) {
            tsag = getTsag() + nemelt;
            return true;
        }
        return false;
    };
};

void selctionSort(ajilchin arr[], int n){
    for (int  i = 0; i < n - 1; i++){
        int k = i;
        for(int j = i + 1; j < n; j++){
            if (arr[k].tsalinBodoh() > arr[j].tsalinBodoh()){
                k = j;
            }
            
        }
        ajilchin temp = arr[i];
        arr[i] = arr[k];
        arr[k] = temp;
    }
    
}

int main(){
    int N;
    cout << "heden ajilchnii medeelel oruulah ve?" << endl;
    cin >> N;
    ajilchin a1[N];

   

    for(int i = 0; i < N; i++){
        cout << "Ajilchinii medeelel: " << i + 1;
        a1[i].getData();
        cout << "\n" ;
    }
    cout<<"\nprimaryData\n";

    for(int i = 0; i < N; i++){
        a1[i].showData();
    }
    
    for (int i = 0; i < N / 2; i++){
        if(a1[i].tsagNemegduuleh(5)){
            cout << "\n(" << i + 1 <<  ") ajilchnii  Tsag amjilttai nemegdlee" ;
        }
    }

    selctionSort(a1, N);
    // tsakingaar erembeleh
    // a1[N].sortTsalin();
    cout << "\n sorted tsag nemegdsen data\n";
    

    for(int i = 0; i < N; i++){
        a1[i].showData();
    }
    return 0;


}