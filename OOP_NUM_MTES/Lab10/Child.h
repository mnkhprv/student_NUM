#ifndef CHILD_H
#define CHILD_H
#include <iostream>
#include "Person.h"
using namespace std;

class Child : public Person
{
  private:
    string favoriteToy;
  public:
    Child(int age, 
          const string& name,
          const string& ssNum,
          const string& favorite) : Person(age, name, ssNum), favoriteToy(favorite){}
    ~Child() = default;
    string getFavoriteToy() { return favoriteToy;};
    void setFavoriteToy(string s){
        if(s.empty()){
        cout << "Алдаа: Тоглоом хоосон байна!\n";
        return;
      }
      favoriteToy = s;
    };
    void display() const override {
      cout << "Хүүхэд: ";
      Person::display();
      cout << endl;
    }
};

#endif