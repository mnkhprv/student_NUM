import { Teacher } from "../domain/Teacher";
export class TeacherService {
  constructor(private teachers: Teacher[]) {}
  getTeacherById(teacherId: string): Teacher | undefined {
    return this.teachers.find(teacher => teacher.id === teacherId);
  }
}