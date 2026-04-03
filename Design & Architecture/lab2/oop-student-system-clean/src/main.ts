import { Student } from "./domain/Student";
import { Teacher } from "./domain/Teacher";
import { Course } from "./domain/Course";
import { CourseService } from "./business/CourseService";
import { StudentService } from "./business/StudentService";
import { TeacherService } from "./business/TeacherService";
import { Task } from "./domain/Task";
import { TaskService } from "./business/TaskService";


// Өгөгдөл бэлтгэх
const student1 = new Student("S001", "Бат", 20);
const student2 = new Student("S002", "Сараа", 21);
const teacher1 = new Teacher("T001", "Мөнх", 35, "Математик");
const softCourse = new Course("C001", "ПХ-ийн Зохиомж ба Архитектур", teacher1.id);
const task1 = new Task("TK001", "Лабораторийн ажил #1", "C001");
const task2 = new Task("TK002", "Гэрийн даалгавар #1", "C001");

// Үйлчилгээний классуудыг үүсгэх
const courseService = new CourseService([softCourse]);
const studentService = new StudentService([student1, student2]);
const teacherService = new TeacherService([teacher1]);
const taskService = new TaskService([task1, task2], studentService);


// Оюутан хичээлд бүртгүүлэх
courseService.enrollStudent("C001", student1);
courseService.enrollStudent("C001", student2);

// Оюутнуудад үнэлгээ оноох
courseService.assignGrade("C001", "S001", 85);
courseService.assignGrade("C001", "S002", 90);

taskService.completeTask("TK001", "S001");
taskService.completeTask("TK001", "S002");
taskService.completeTask("TK002", "S001");

// Дүнгийн жагсаалт авах
console.log(`${softCourse.name} хичээлийн үнэлгээ:`);
softCourse.getStudentGrades().forEach((grade, studentId) => {
  const student = studentService.findStudentById(studentId);
  console.log(`${student?.name}: ${grade} оноо`);
});

// Багшийн мэдээлэл
const teacher = teacherService.getTeacherById("T001");
console.log(`${teacher?.name} багш ${teacher?.subject} хичээл зааж байна.`);


// Хичээлийн даалгавруудыг харуулах
console.log(`\n${softCourse.name} hicheeliin Daalgavaruud:`);
taskService.getTasksByCourse("C001").forEach(task => {
  console.log(`\Daalgavar: ${task.title}`);
  const completedStudents = taskService.getCompletedStudents(task.id);
  if (completedStudents.length === 0) {
    console.log("Guitsetgesen oyutan baihgui.");
  } else {
    completedStudents.forEach(student => {
      console.log(`${student.name} Guitsetgesen.`);
    });
  }
});