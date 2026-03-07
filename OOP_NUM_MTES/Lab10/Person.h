#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>

using namespace std;

class Person 
{
  protected:
    string name;
    string ssNum;
    int age;
  public:
    Person(int age, string name, string ssNum)
        : age(age < 0 ? 0 : age),
          name(age < 0 ? "" : name),
          ssNum(age < 0 ? "" : ssNum){}
    ~Person() = default;
    string getName() { return name;};
    string getSsnum(){ return ssNum;};
    int getAge(){ return age;};
    void setName(string s) {
      if(s.empty()){
        cout << "Алдаа: нэр хоосон байна!\n";
        return;
      }
      name = s;
    };
    void setSsnum(string s) {
      if(s.empty()){
        cout << "Алдаа: ssNUM хоосон байна!\n";
        return;
      }
      ssNum = s;
    };
    void setAge(int n) {
      if(n < 0){
         cout << "Алдаа: нас хоосон байна!\n";
        return;
      }
      age = n;
    };
    virtual void display() const {
      cout << "Нэр: " << name << ", Нас: " << age << ", SSN: " << ssNum;
    }
  };
#endif