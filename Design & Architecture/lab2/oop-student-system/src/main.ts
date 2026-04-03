import { Student } from "./models/Student";
import { Teacher } from "./models/Teacher";
import { Course } from "./models/Course";

// Оюутан үүсгэх
const student1 = new Student("Бат", 20, "S123");
const student2 = new Student("Сараа", 21, "S124");

// Багш үүсгэх
const teacher1 = new Teacher("Мөнх", 35, "Математик");

// Хичээл үүсгэх
const mathCourse = new Course("Математик", teacher1.name);

// Оюутнуудыг хичээлд бүртгэх
mathCourse.enrollStudent(student1);
mathCourse.enrollStudent(student2);

// Оюутнуудад үнэлгээ өгөх
mathCourse.assignGrade(student1, 85);
mathCourse.assignGrade(student2, 90);

// Дүнгийн жагсаалт авах
console.log(`${mathCourse.name} хичээлийн үнэлгээ:`);
mathCourse.getStudentGrades().forEach((grade, student) => {
 console.log(`${student.name}: ${grade} оноо`);
});

// Багшийн мэдээлэл
console.log(teacher1.teach());

const average = mathCourse.calculateAverage();
console.log(`Dundaj onoo: ${average}`)

console.log(teacher1.getRole());
console.log(student1.getRole());
