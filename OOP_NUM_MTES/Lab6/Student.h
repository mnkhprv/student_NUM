#ifndef STUDENT_H
#define STUDENT_H
#include<vector>

class Student {
    private:
        // оюутны дугаар(private хандалтын түвшинтэй тэмдэгтийн цуваа хадгалах хаяган хувьсагч)
        char* studentId;
        // голч (private хандалтын түвшинтэй 0-4 хооронд байх бутархай тоо) 
        float gpa;
        // тоо (private хандалтын түвшинтэй хэдэн объект үүссэн байгааг тоолох статик гишүүн өгөгдөл)
        static int count;
        static int idCounter;

        char* generateStudentId();

        static std::vector<char*> usedId;
    public:
        // нэр (public хандалтын түвшинтэй тэмдэгтийн цуваа хадгалах хаяган хувьсагч)
        char* name;
        // курс (public хандалтын түвшинтэй эерэг бүхэл тоо)
        int course;
        
    // Байгуулагчууд
        Student();
        Student(const char* n, const char* id, int c, float g);
        Student(const Student& other);
    // Устгагч
        ~Student();
    // Хуулагч функц
        Student& operator=(const Student& other);
        
    // Харьцуулах функцууд - курсээр
        bool greatThan(const Student& other) const;
        bool lessThan(const Student& other) const;
        bool isEqual(const Student& other) const;
    // Харьцуулах функцууд - нэрээр
        bool before(const Student& other) const;
        bool after(const Student& other) const;
        
    // Getter функцууд
        const char* getName() const;
        const char* getStudentId() const;
        int getCourse() const;
        float getGpa() const;
        
    // Setter функцууд
        void setName(const char* n);
        void setStudentId(const char* id);
        void setCourse(int c);
        void setGpa(float g);
        
    // Статик функц
        static int getCount();
        
    // Хэвлэх функц
        void getData();
        void print() const;

};
#endif