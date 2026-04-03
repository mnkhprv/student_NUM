export class Person {
  constructor(public name: string, public age: number) {}
  introduce(): string {
    return `Сайн байна уу! Намайг ${this.name} гэдэг. Би ${this.age} настай.`;
  }

  getRole(): string {
    return 'Person';
  }

}