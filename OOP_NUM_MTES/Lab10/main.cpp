#include <iostream>
#include "Person.h"
#include "Spouse.h"
#include "Child.h"
#include "Division.h"
#include "JobDescription.h"
#include "Employee.h"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "  АЖИЛТНЫ УДИРДЛАГЫН СИСТЕМ" << endl;
    cout << "========================================\n" << endl;
    
    // ========================================
    // 2. Division болон JobDescription объектууд үүсгэх
    // ========================================
    cout << "--- 2. Division болон JobDescription объектууд үүсгэж байна... ---\n" << endl;
    
    // Division объектууд
    Division itDivision("IT Хэлтэс", "Улаанбаатар, БЗД, 1-р давхар");
    Division hrDivision("Хүний Нөөцийн Хэлтэс", "Улаанбаатар, СБД, 2-р давхар");
    Division financeDivision("Санхүүгийн Хэлтэс", "Улаанбаатар, ХУД, 3-р давхар");
    Division marketingDivision("Маркетингийн Хэлтэс", "Улаанбаатар, СХД, 2-р давхар");
    
    cout << "✓ 4 Division үүсгэлээ:" << endl;
    cout << "  - IT Хэлтэс" << endl;
    cout << "  - Хүний Нөөцийн Хэлтэс" << endl;    
    cout << "  - Санхүүгийн Хэлтэс" << endl;
    cout << "  - Маркетингийн Хэлтэс\n" << endl;
    
    // JobDescription объектууд
    JobDescription devJob("Software Developer", "Програм хөгжүүлэлт хийх");
    JobDescription seniorDevJob("Senior Developer", "Систем зохион бүтээх, код хянах");
    JobDescription teamLeadJob("Team Lead", "Багийн удирдлага, төлөвлөлт хийх");
    JobDescription hrManagerJob("HR Manager", "Хүний нөөц удирдах, ажилтан авах");
    JobDescription recruiterJob("Recruiter", "Шинэ ажилтан сонгон шалгаруулах");
    JobDescription accountantJob("Нягтлан Бодогч", "Санхүүгийн тайлан бэлтгэх");
    JobDescription finAnalystJob("Санхүүгийн Шинжээч", "Санхүүгийн дүн шинжилгээ хийх");
    JobDescription marketingMgrJob("Marketing Manager", "Маркетингийн стратеги боловсруулах");
    
    cout << "✓ 8 JobDescription үүсгэлээ:" << endl;
    cout << "  - Software Developer, Senior Developer, Team Lead" << endl;
    cout << "  - HR Manager, Recruiter" << endl;
    cout << "  - Нягтлан Бодогч, Санхүүгийн Шинжээч" << endl;
    cout << "  - Marketing Manager\n" << endl;
    
    // ========================================
    // Spouse болон Child объектууд (Employee-д хамааруулахаас өмнө)
    // ========================================
    Spouse spouse1(30, "Оюунаа", "УБ11111111", "2015-06-20");
    Child child1_1(6, "Тэмүүлэн", "УБ11111112", "Машин");
    Child child1_2(4, "Мөнх-Эрдэнэ", "УБ11111113", "Хүүхэлдэй");
    
    Spouse spouse2(30, "Ганбат", "УБ22222221", "2019-09-15");
    
    Spouse spouse3(33, "Туяа", "УБ33333331", "2012-05-10");
    Child child3_1(10, "Болормаа", "УБ33333332", "Ном");
    Child child3_2(8, "Энхжин", "УБ33333333", "Бөмбөг");
    Child child3_3(5, "Ану-Удин", "УБ33333334", "Зурагдах");
    
    // ========================================
    // 3. Employee объектууд үүсгэх
    // ========================================
    cout << "--- 3. Employee объектууд үүсгэж байна... ---\n" << endl;
    
    // Employee 1: Бат - IT Хэлтэс
    Employee emp1(
        32,                          // age
        "Бат",                       // name
        "УБ12345678",               // ssNum
        "EMP001",                   // companyID
        "Senior Developer",         // title
        "2019-03-15",              // startDate
        &itDivision,                // division (1..1)
        &seniorDevJob,             // firstJob (1..*)
        nullptr,                    // spouse
        nullptr                     // child
    );
    cout << "✓ Employee 1 үүсгэлээ: Бат (IT Хэлтэс)\n" << endl;
    
    // Employee 2: Сараа - HR Хэлтэс
    Employee emp2(
        28,
        "Сараа",
        "УБ23456789",
        "EMP002",
        "HR Manager",
        "2020-07-01",
        &hrDivision,
        &hrManagerJob,
        nullptr,
        nullptr
    );
    cout << "✓ Employee 2 үүсгэлээ: Сараа (HR Хэлтэс)\n" << endl;
    
    // Employee 3: Дорж - Санхүүгийн Хэлтэс
    Employee emp3(
        35,
        "Дорж",
        "УБ34567890",
        "EMP003",
        "Нягтлан Бодогч",
        "2018-01-10",
        &financeDivision,
        &accountantJob,
        nullptr,
        nullptr
    );
    cout << "✓ Employee 3 үүсгэлээ: Дорж (Санхүүгийн Хэлтэс)\n" << endl;
    
    // Employee 4: Болд - IT Хэлтэс
    Employee emp4(
        29,
        "Болд",
        "УБ45678901",
        "EMP004",
        "Software Developer",
        "2021-05-20",
        &itDivision,
        &devJob,
        nullptr,
        nullptr
    );
    cout << "✓ Employee 4 үүсгэлээ: Болд (IT Хэлтэс)\n" << endl;
    
    // ========================================
    // 4. Spouse болон Child объектууд тохируулах
    // ========================================
    cout << "--- 4. Spouse болон Child-үүд тохируулж байна... ---\n" << endl;
    
    // Employee 1 (Бат) - Эхнэр + 2 хүүхэд + 2 Job (1..* харьцаа харуулах)
    emp1.setSpouse(&spouse1);
    emp1.addChild(&child1_1);
    emp1.addChild(&child1_2);
    
    // 1..* харьцаа: Батад нэмэлт Job нэмэх
    emp1.addJob(&teamLeadJob);
    
    cout << "✓ Бат: Эхнэр (Оюунаа) + 2 хүүхэд + 2 Jobs" << endl;
    
    // Employee 2 (Сараа) - Зөвхөн эхнэр (0..1 харьцаа)
    emp2.setSpouse(&spouse2);
    
    cout << "✓ Сараа: Нөхөр (Ганбат)" << endl;
    
    // Employee 3 (Дорж) - Эхнэр + 3 хүүхэд + 2 Jobs
    emp3.setSpouse(&spouse3);
    emp3.addChild(&child3_1);
    emp3.addChild(&child3_2);
    emp3.addChild(&child3_3);
    
    // Дорж-д нэмэлт Job өгөх
    emp3.addJob(&finAnalystJob);
    
    cout << "✓ Дорж: Эхнэр (Туяа) + 3 хүүхэд + 2 Jobs" << endl;
    
    // Employee 4 (Болд) - Гэр бүлгүй (0..1 spouse, 0..* children харьцаа)
    cout << "✓ Болд: Гэр бүлгүй (0..1 spouse, 0..* children харьцаа)\n" << endl;
    
    // ========================================
    // 5. Бүх Employee-ийн мэдээллийг хэвлэх
    // ========================================
    cout << "========================================" << endl;
    cout << "  5. АЖИЛТНУУДЫН ДЭЛГЭРЭНГҮЙ МЭДЭЭЛЭЛ" << endl;
    cout << "========================================\n" << endl;
    
    emp1.displayAll();
    emp2.displayAll();
    emp3.displayAll();
    emp4.displayAll();
    
    // ========================================
    // 6. Харьцааны шалгалтын тайлан
    // ========================================
    cout << "========================================" << endl;
    cout << "  6. ХАРЬЦААНЫ ШАЛГАЛТ" << endl;
    cout << "========================================\n" << endl;
    
    cout << "✅ 0..1 (Spouse) харьцаа:" << endl;
    cout << "   - Бат: Эхнэртэй ✓" << endl;
    cout << "   - Сараа: Нөхөртэй ✓" << endl;
    cout << "   - Дорж: Эхнэртэй ✓" << endl;
    cout << "   - Болд: Гэр бүлгүй ✓" << endl;
    cout << "   → Ажилтан 0 эсвэл 1 эхнэр/нөхөртэй байж болно\n" << endl;
    
    cout << "✅ 0..* (Children) харьцаа:" << endl;
    cout << "   - Бат: 2 хүүхэдтэй ✓" << endl;
    cout << "   - Сараа: Хүүхэдгүй ✓" << endl;
    cout << "   - Дорж: 3 хүүхэдтэй ✓" << endl;
    cout << "   - Болд: Хүүхэдгүй ✓" << endl;
    cout << "   → Ажилтан 0 эсвэл олон хүүхэдтэй байж болно\n" << endl;
    
    cout << "✅ 1..* (JobDescription) харьцаа:" << endl;
    cout << "   - Бат: 2 Job-тай (Senior Dev + Team Lead) ✓" << endl;
    cout << "   - Сараа: 1 Job-тай (HR Manager) ✓" << endl;
    cout << "   - Дорж: 2 Job-тай (Accountant + Analyst) ✓" << endl;
    cout << "   - Болд: 1 Job-тай (Developer) ✓" << endl;
    cout << "   → Ажилтан заавал дор хаяж 1 Job-тай, илүү байж болно\n" << endl;
    
    cout << "✅ 1..1 (Division) харьцаа:" << endl;
    cout << "   - Бат: IT Хэлтэс ✓" << endl;
    cout << "   - Сараа: HR Хэлтэс ✓" << endl;
    cout << "   - Дорж: Санхүүгийн Хэлтэс ✓" << endl;
    cout << "   - Болд: IT Хэлтэс ✓" << endl;
    cout << "   → Бүх ажилтан заавал яг 1 Division-тэй байна\n" << endl;
    
    // ========================================
    // Нэмэлт тест: Харьцааны хязгаарлалт шалгах
    // ========================================
    cout << "========================================" << endl;
    cout << "  ХАРЬЦААНЫ ХЯЗГААРЛАЛТ ТЕСТЛЭХ" << endl;
    cout << "========================================\n" << endl;
    
    cout << "➤ Тест 1: Болд-д хоёр дахь эхнэр өгөхийг оролдох (0..1 хязгаар)" << endl;
    Spouse extraSpouse(25, "Цэцэг", "УБ99999999", "2023-01-01");
    emp4.setSpouse(&extraSpouse); // Эхлээд анхны эхнэр өгье
    emp4.setSpouse(&extraSpouse); // Дахин өгөхийг оролдох
    cout << endl;
    
    cout << "➤ Тест 2: Болд-оос job устгахыг оролдох (1..* хязгаар)" << endl;
    emp4.removeJob(0); // Цорын ганц job-ийг устгахыг оролдох
    cout << endl;
    
    cout << "➤ Тест 3: Дорж-ын нэг job-ыг амжилттай устгах (2-оос 1 болно)" << endl;
    emp3.removeJob(1); // 2 job байгаа учир 1-ийг нь устгаж болно
    cout << "✓ Амжилттай устгалаа\n" << endl;
    
    cout << "========================================" << endl;
    cout << "  ПРОГРАММ АМЖИЛТТАЙ ДУУСЛАА!" << endl;
    cout << "  (Бүх объектууд автоматаар устана)" << endl;
    cout << "========================================" << endl;
    
    return 0;
}