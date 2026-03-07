#ifndef JOBDESCRIPTION_H
#define JOBDESCRIPTION_H
#include <iostream>

using namespace std;

class JobDescription
{
  private:
    string jobTitle;
    string description;
  public:
    JobDescription(const string& title, const string& desc) 
        : jobTitle(title), description(desc){}
    ~JobDescription() = default;
    
    string getJobTitle() {return jobTitle;};
    string getDescription() {return description;};
    
    void setJobTitle(const string& s) {
      if(s.empty()){
        cout << "Алдаа: JobTitle хоосон байна\n";
        return;
      }
      jobTitle = s;
    };
    
    void setDescription(const string& s) {
      if(s.empty()){
        cout << "Алдаа: Description хоосон байна\n";
        return;
      }
      description = s;
    };
    void display() const {
      cout << "    Албан тушаал: " << jobTitle 
           << ", Тайлбар: " << description <<  endl;
    }
};

#endif
