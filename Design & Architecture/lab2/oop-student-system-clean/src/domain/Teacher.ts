import { Person } from "./Person";
export class Teacher extends Person {
  constructor(id: string, name: string, age: number, public subject: string) {
  super(id, name, age);
  }
}