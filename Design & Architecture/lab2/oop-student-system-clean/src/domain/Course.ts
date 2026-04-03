import { Student } from "./Student";
export class Course {
  public students: Student[] = [];
  private grades: Map<string, number> = new Map();
  
  constructor(
    public id: string, 
    public name: string, 
    public teacherId: string
  ) {}
  
  enrollStudent(student: Student): void {
    this.students.push(student);
  }
  assignGrade(studentId: string, grade: number): void {
    this.grades.set(studentId, grade);
  }
  getStudentGrades(): Map<string, number> {
  return this.grades;
  }
}