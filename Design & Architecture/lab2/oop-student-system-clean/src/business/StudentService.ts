import { Student } from "../domain/Student";
export class StudentService {
  constructor(private students: Student[]) {}
  findStudentById(studentId: string): Student | undefined {
    return this.students.find(student => student.id === studentId);
  }
}