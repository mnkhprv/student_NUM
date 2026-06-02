class StudentList {
  constructor(private readonly names: string[]) {}

  filterLongNames(minLength: number): string[] {
    return this.names.filter((name) => name.length > minLength);
  }

  toUpperCase(names: string[]): string[] {
    return names.map((name) => name.toUpperCase());
  }
}

type Unary<T> = (value: T) => T;

function pipe<T>(...fns: Unary<T>[]): Unary<T> {
  return (value: T) => fns.reduce((current, fn) => fn(current), value);
}

const filterLongNames =
  (minLength: number) =>
  (names: string[]): string[] =>
    names.filter((name) => name.length > minLength);

const toUpperCase = (names: string[]): string[] => names.map((name) => name.toUpperCase());

const students = ["Bat", "Dorj", "Suren"];

const oopStudentList = new StudentList(students);
const oopResult = oopStudentList.toUpperCase(oopStudentList.filterLongNames(4));

const fpTransform = pipe<string[]>(filterLongNames(4), toUpperCase);
const fpResult = fpTransform(students);

console.log("Task 1");
console.log("OOP result:", oopResult);
console.log("FP result:", fpResult);
console.log("");
console.log("Answers");
console.log("1. FP reduces coupling more because each transformation is an independent pure function.");
console.log("2. OOP keeps state in StudentList through the names field. FP works with input/output values only.");
