import { Student } from "./Student";
export class Course {
  private students: Student[] = new Array();
  private grades: Map<Student, number> = new Map();
  constructor(public name: string, public teacher: string) {}
  enrollStudent(student: Student) {
    this.students.push(student);
  }
  assignGrade(student: Student, grade: number) {
    this.grades.set(student, grade);
  }
  getStudentGrades(): Map<Student, number> {
    return this.grades;
  }

  calculateAverage(): number {
    if (this.grades.size === 0) return 0;
    const total = Array.from(this.grades.values()).reduce(
      (sum, grade) => sum + grade, 0
    );

    return total / this.grades.size ;
    // implement
  }

}