#ifndef DIVISION_H
#define DIVISION_H
#include <iostream>

using namespace std;

class Division
{
  private:
    string divisionName;
    string location;
  public:
    Division(const string& d, const string& loc) 
        : divisionName(d), location(loc){}
    ~Division() = default;
    
    string getDivisionName(){ return divisionName;};
    string getLocation(){ return location;};
    
    void setDivisionName(const string& s){
      if(s.empty()){
        cout << "Алдаа: Division хоосон байна!\n";
        return;
      }
      divisionName = s;
    };
    
    void setLocation(const string& s){
      if(s.empty()){
        cout << "Алдаа: Division хоосон байна!\n";
        return;
      }
      location = s;
    };
    void display() const {
      cout << "  Хэлтэс: " << divisionName << " (" << location << ")" << endl;
    }
};

#endif