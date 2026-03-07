#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include "Person.h"
#include "Spouse.h"
#include "Child.h"
#include "Division.h"
#include "JobDescription.h"
#include <vector>
using namespace std;

class Employee : public Person
{
  private:
    string companyID;
    string title;
    string startDate;

    Spouse* spouse;               // 0 or 1
    vector<Child*> children;      // 0..*
    vector<JobDescription*> jobs; // 1..*
    Division* division;           // 1
  public:
    Employee(int age,
            const string& name,
            const string& ssNum,
            const string& ID,
            const string& ttl,
            const string& date,
            Division* div,
            JobDescription* firstJob,
            Spouse* sps,
            Child* kid)
            :Person(age, name, ssNum),
           companyID(ID), title(ttl), startDate(date),
           division(nullptr), spouse(nullptr)
    {
      if (!div) {
          cout << "Алдаа: Employee нь заавал 1 Division-тэй байх ёстой!" << endl;
          return;
      }
      division = div;

      if (!firstJob) {
          cout << "Алдаа: Employee нь дор хаяж 1 JobDescription-тэй байх ёстой!" << endl;
          return;
      }
      jobs.push_back(firstJob);
    }
    string getCompanyID(){ return companyID;}
    string getTitle(){return title;}
    string getStartDate(){return startDate;}
    void setCompanyID(const string& s) {
      if (s.empty()) {
        cout << "Алдаа: ID хоосон байна!" << endl;
        return;
      }
      companyID = s;
    }
    void setTitle(const string& s) {
      if (s.empty()) {
        cout << "Алдаа: Title хоосон байна!" << endl;
        return;
      }
      title = s;
    }
    void setStartDate(const string& s) {
      if (s.empty()) {
        cout << "Алдаа: Date хоосон байна!" << endl;
        return;
      }
      startDate = s;
    }
    void setSpouse(Spouse* s) {
      if (!s) {return;}
      if (spouse != nullptr) {
        cout << "Алдаа: Аль хэдийн эхнэр/нөхөртэй байна!" << endl;
        return;
      }
      spouse = s;
    }
    void removeSpouse(){
      if (!spouse) {
        cout << "Анхааруулга: Эхнэр/нөхөргүй байна!" << endl;
        return;
      }
      spouse = nullptr;
    }
    void addChild(Child* c) { 
      if (!c) {
        cout << "Алдаа: null Child нэмж болохгүй!" << endl;
        return;
      }
      children.push_back(c);
    }
    void removeChild(int i){
      if (i < 0 || i >= children.size()) {
        cout << "Алдаа: Index буруу байна!" << endl;
        return;
      }
      
      children.erase(children.begin() + i);
    }
    void addJob(JobDescription* j){
      if(!j) {
        cout << "Алдаа: null Job нэмж болохгүй!" << endl;
        return;
      }
      jobs.push_back(j);
    }
    void removeJob(int i){
      if(i < 0 || i >= jobs.size()) {
        cout << "Алдаа: Index буруу байна!" << endl;
        return;
      }
      if(jobs.size() == 1){
        cout << "Алдаа: Employee дор хаяж 1 Job байх ёстой!" << endl;
        return;
      }
      jobs.erase(jobs.begin() + i);
    }
    void setDivision(Division* div){
      if(!div) {
        cout << "Алдаа: Division null байж болохгүй!" << endl;
        return;
      }
      division = div;
    }
    void displayAll() const {
      cout << "========================================\n" << endl;
      cout << "АЖИЛТНЫ МЭДЭЭЛЭЛ" << endl;
      Person::display();
      cout << endl;
      cout << "  Компанийн ID: " << companyID << endl;
      cout << "  Албан тушаал: " << title << endl;
      cout << "  Эхэлсэн огноо: " << startDate << endl;
      if (division) {
        division->display();
      }
      cout << "  Ажлын мэдээлэл (" << jobs.size() << "):" << endl;
      for (size_t i = 0; i < jobs.size(); i++) {
        jobs[i]->display();
      }
      if (spouse) {
        spouse->display();
      } else {
        cout << "  Эхнэр/Нөхөр: Байхгүй" << endl;
      }
      if (children.empty()) {
        cout << "  Хүүхдүүд: Байхгүй" << endl;
      } else {
        cout << "  Хүүхдүүд (" << children.size() << "):" << endl;
        for (size_t i = 0; i < children.size(); i++) {
          children[i]->display();
        }
      }
      cout << "========================================\n" << endl;
    }
};

#endif