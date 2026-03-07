#include "Student.h"
#include <cstring>
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

// 
vector<char*> Student :: usedId;
// Статик гишүүн өгөгдлийг эхлүүлэх
int Student::count = 0;
int Student::idCounter = 1;

char* Student::generateStudentId() {
    char buff[20];
    sprintf(buff, "25B1NUM%04d", idCounter);
    idCounter++;
    char* newId = new char[strlen(buff) + 1];
    strcpy(newId, buff);
    usedId.push_back(newId);
    return newId;
}

// Анхдагч байгуулагч
Student::Student() {
    this->name = new char[1];
    strcpy(this->name, "");
    
    this->studentId = generateStudentId();
        
    this->course = 1;
    this->gpa = 0.0f;
    
    count++;
}

// Параметертэй байгуулагч
Student::Student(const char* n, const char* id, int c, float g) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);
    
    studentId = new char[strlen(id) + 1];
    strcpy(studentId, id);
    
    course = c;
    gpa = (g >= 0.0f && g <= 4.0f) ? g : 0.0f;
    
    count++;
}

// Хуулагч байгуулагч
Student::Student(const Student& other) {
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    
    this->studentId = new char[strlen(other.studentId) + 1];
    strcpy(this->studentId, other.studentId);
    
    this->course = other.course;
    this->gpa = other.gpa;
    
    count++;
}

// Устгагч
Student::~Student() {
    delete[] this->name;
    delete[] this->studentId;
    count--;
}

// Хуулагч функц (оператор=)
Student& Student::operator=(const Student& other) {
    if (this == &other) {
        return *this;
    }
    
    delete[] this->name;
    delete[] this->studentId;
    
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    
    this->studentId = new char[strlen(other.studentId) + 1];
    strcpy(this->studentId, other.studentId);
    
    this->course = other.course;
    this->gpa = other.gpa;
    
    return *this;
}

// Курсээр харьцуулах функцууд
bool Student::greatThan(const Student& other) const {
    return this->course > other.course;
}

bool Student::lessThan(const Student& other) const {
    return this->course < other.course;
}

bool Student::isEqual(const Student& other) const {
    return this->course == other.course;
}

// Нэрээр харьцуулах функцууд

bool Student::before(const Student& other) const {
    return strcmp(this->name, other.name) < 0;
}

bool Student::after(const Student& other) const {
    return strcmp(this->name, other.name) > 0;
}

// Getter функцууд
const char* Student::getName() const {return this->name;}

const char* Student::getStudentId() const {return this->studentId;}

int Student::getCourse() const {return this->course;}

float Student::getGpa() const {return this->gpa;}

// Setter функцууд
void Student::setName(const char* n) {
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "ner dahin oruulna uu!" << endl;
        setName(n);
    }
    else{
        delete[] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
}

void Student::setStudentId(const char* id) {
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        setStudentId(id);
    }
    else{
        delete[] this->studentId;
        this->studentId = generateStudentId();
    }
    cout << "onooson ID:" << studentId << endl;
}

void Student::setCourse(int c) {
    if(cin.fail() || c <= 0){  
        cin.clear();
        cin.ignore();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Kurs buruu oruulsan!\n";
        course = 1;
    }
    else{
        this->course = c;
    }
}
void Student::setGpa(float g) {
    if (g < 0.0f || g > 4.0f) {
        cout << "Zuv GPA oruulna uu (0.0-4.0). GPA-g 0.0-eer onoogloo.\n";
        gpa = 0.0f;
    } else {
        gpa = g;
    }
}



// Статик функц
int Student::getCount() {return count;}
// 
void Student::getData() {
    char n[30];
    int c;
    float g;

    cout << "\nNer oruulna uu: ";
    cin >> n;
    setName(n);

    cout << "Kurs (1-5): ";
    cin >> c;
    setCourse(c);

    cout << "GPA (0.0-4.0): ";
    cin >> g;
    setGpa(g);
}

// Хэвлэх функц
void Student::print() const {
    cout << "Нэр: " << name 
         << ", Дугаар: " << studentId 
         << ", Курс: " << course 
         << ", Голч: " << gpa << endl;
}