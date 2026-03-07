#ifndef SPOUSE_H
#define SPOUSE_H
#include <iostream>
#include "Person.h"

using namespace std;

class Spouse : public Person 
{
  private:
    string anniversaryDate;
  public:
    Spouse(int age, 
          const string& name,
          const string& ssNum,
          const string& date) : Person(age, name, ssNum), anniversaryDate(date){}
    ~Spouse() = default;
    string getAnniversaryDate() const { return anniversaryDate;};
    void setAnniversaryDate(const string& s) {
      if(s.empty()){
        cout << "Алдаа: Огноо хоосон байна!\n";
        return;
      }
      anniversaryDate = s;
    };
    void display() const override {
      cout << "  Эхнэр/Нөхөр: ";
      Person::display();
      cout << endl;
    }
};

#endif