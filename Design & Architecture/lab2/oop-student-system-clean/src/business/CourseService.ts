import { Course } from "../domain/Course";
import { Student } from "../domain/Student";
export class CourseService {
  constructor(private courses: Course[]) {}
  enrollStudent(courseId: string, student: Student): void {
    const course = this.courses.find(course => course.id === courseId);
    if (course) {
      course.enrollStudent(student);
    } else {
       throw new Error("Хичээл олдсонгүй!");
    }
  }
  assignGrade(courseId: string, studentId: string, grade: number): void {
    const course = this.courses.find(course => course.id === courseId);
    if (course) {
      course.assignGrade(studentId, grade);
    } else {
      throw new Error("Хичээл олдсонгүй!");
    }
  }
}