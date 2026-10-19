export abstract class Person {
  constructor(
    public id: string,
    public name: string,
    public age: number
    ) {}
    introduce(): string {
    return 'Сайн байна уу! Намайг ${this.name} гэдэг.';
  }
}