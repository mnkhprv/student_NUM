import { Person } from "./Person";
export class Student extends Person {
  public courses: string[] = []; // Оюутны сонгосон хичээлүүд
  constructor(id: string, name: string, age: number) {
  super(id, name, age);
  }
}