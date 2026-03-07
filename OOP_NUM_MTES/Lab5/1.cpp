#include <iostream>
#include <cstring>
#include <limits>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class ajilchin {
private:
    int dugaar;
    char* ner;
    char* alba;
    float tsag;
    static vector<int> usedD;
    
    float zahirliinTsalin() {
        if(strcmp(alba, "zahiral") == 0){
            int uTsalin, une = 5000;
            uTsalin = tsag * une;
            return uTsalin + 200000;
        }
        return 0;
    }
    
    int generateUniqueID() {
        int id;
        do{
            id = 1 + rand() % 10000;
        }while (find(usedD.begin(), usedD.end(), id) != usedD.end());
        usedD.push_back(id);
        return id;
    }

public:
    ajilchin(){
        dugaar = generateUniqueID();
        ner = new char[1];
        strcpy(ner, "");
        alba = new char[10];
        strcpy(alba, "ajilchin");
        tsag = 0;
    }

    ajilchin(int i, const char* n, const char* a, float t){
        if(strlen(n) > 20 || strlen(a) > 10 || t < 0) {
            cout << "buruu parametruud" << endl;
            dugaar = generateUniqueID();
            ner = new char[1];
            strcpy(ner, "");
            alba = new char[10];
            strcpy(alba, "ajilchin");
            tsag = 0;
            return;
        }
        dugaar = generateUniqueID();
        ner = new char[strlen(n) + 1];
        strcpy(ner, n);
        alba = new char[strlen(a) + 1];
        strcpy(alba, a);
        tsag = t;
    }

    ajilchin(const ajilchin& other) {
        dugaar = other.dugaar;
        ner = new char[strlen(other.ner) + 1];
        strcpy(ner, other.ner);
        alba = new char[strlen(other.alba) + 1];
        strcpy(alba, other.alba);
        tsag = other.tsag;
    }

    ajilchin& operator=(const ajilchin& other) {
        if (this != &other) {
            delete[] ner;
            delete[] alba;
            
            dugaar = other.dugaar;
            ner = new char[strlen(other.ner) + 1];
            strcpy(ner, other.ner);
            alba = new char[strlen(other.alba) + 1];
            strcpy(alba, other.alba);
            tsag = other.tsag;
        }
        return *this;
    }

    ~ajilchin(){
        delete[] ner;
        delete[] alba;
        auto it = find(usedD.begin(), usedD.end(), dugaar);
        if (it != usedD.end()) usedD.erase(it);
    }
    
    void getData(){
        char n[21], a[11];
        float t; int d;

        cout << "Dugaar: ";
        while(!(cin >> d) || d <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "0-ees ih dugaar zuv oruulna uu:\n Dugaar: ";
        }
        setDugaar(d);
        cout << "Ner: ";
        cin >> n;
        setNer(n);
        cout << "Alba: ";
        cin >> a;
        setAlba(a);
        cout << "Tsag: ";
        while(!(cin >> t) || t < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "0-ees deesh tsag zuv oruulna uu: ";
        }
        setTsag(t);
    }

    void setNer(const char n[]){
        if(strlen(n) > 20){
            cout << "ner 20 temdegtees burdeh ystoi!" << endl;
            return;
        }
        delete[] ner;
        ner = new char[strlen(n) + 1];
        strcpy(ner, n);
    }
    
    char* getNer() const {return ner;}
    
    void setDugaar(int d){
        if (d <= 0 || find(usedD.begin(), usedD.end(), d) != usedD.end()){
            auto it = find(usedD.begin(), usedD.end(), dugaar);
            if (it != usedD.end()) {
                usedD.erase(it);
            }
            dugaar = generateUniqueID();
            cout << "Buruu esvel davhardsan dugaar. Shine unique ID onoogdloo: ";
        } else {
            auto it = find(usedD.begin(), usedD.end(), dugaar);
            if (it != usedD.end()) {
                usedD.erase(it);
            }
            dugaar = d;
            usedD.push_back(d);
            cout << "Onooson dugaar: ";
        }
        cout << dugaar << endl;
    }
    
    int getDugaar() const {return dugaar;}
    void setAlba(const char n[]){
        if(strlen(n) > 10){
            cout << "alba 10 temdegtees burdeh ystoi!" << endl;
            return;
        }
        delete[] alba;
        alba = new char[strlen(n) + 1];
        strcpy(alba, n);
    }
    
    char* getAlba() const {return alba;}
    
    void setTsag(float t){
        if (t < 0){
            cout << "0-ees deesh tsag zuv oruulna uu!" << endl;
            return;
        }
        tsag = t;
    }
    
    float getTsag() const {return tsag;}

    float tsalinBodoh() const {
        if(strcmp(alba, "zahiral") == 0){
            int uTsalin, une = 5000;
            uTsalin = tsag * une;
            return uTsalin + 200000;
        }
        float une = 5000;
        float tsalin = tsag * une;
        return tsalin;
    }
    
    void showData() const {
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
    }
    
    static bool compareSalary(const ajilchin &a, const ajilchin &b) {
        return a.tsalinBodoh() < b.tsalinBodoh();
    }

    static bool compareName(const ajilchin &a, const ajilchin &b) {
        return strcmp(a.getNer(), b.getNer()) < 0;
    }
};

void selectionSort(vector<ajilchin> &a, int n){
    for (int i = 0; i < n - 1; i++){
        int k = i;
        for(int j = i + 1; j < n; j++){
            if (a[k].tsalinBodoh() > a[j].tsalinBodoh()){
                k = j;
            }
        }
        if (k != i) {
            ajilchin temp = a[i];
            a[i] = a[k];
            a[k] = temp;
        }
    }
}

vector<int> ajilchin::usedD;

int main(){
    srand(time(0));
    
    int N;
    cout << "heden ajilchnii medeelel oruulah ve?" << endl;
    while (!(cin >> N) || N <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Zuv too oruulna uu: ";
    }

    vector<ajilchin> ajilchid(N); 

    for(int i = 0; i < N; i++){
        cout << "\nAjilchinii medeelel: " << i + 1 << "\n";
        ajilchid[i].getData(); 
    }
    
    selectionSort(ajilchid, N);
    cout << "\nTsalingaar eremblesen:\n";
    for(const auto &a : ajilchid) {
        a.showData();
    }

    return 0;
}

