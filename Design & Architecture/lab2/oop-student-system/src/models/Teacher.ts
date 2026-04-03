import { Person } from "./Person";
export class Teacher extends Person {
  constructor(name: string, age: number, public subject: string) {
    super(name, age);
  }
  teach(): string {
    return `${this.name} багш ${this.subject} хичээл зааж байна.`;
  }

  getRole(): string {
    return 'Teacher';
  }
}