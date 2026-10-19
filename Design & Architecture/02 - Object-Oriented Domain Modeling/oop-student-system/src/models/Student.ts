import { Person } from "./Person";
export class Student extends Person {
  private courses: string[] = [];
  constructor(name: string, age: number, public studentId: string) {
    super(name, age);
  }
  enroll(course: string) {
    this.courses.push(course);
  }

  getCourse() :string[] {
    return this.courses;
  }
  getRole(): string {
    return 'Student';
  }

}
