type Student = {
  id: string;
  name: string;
  credits: number;
};

class StudentRepo {
  private readonly storage: Student[] = [];

  save(student: Student): Student {
    this.storage.push(student);
    return student;
  }

  all(): Student[] {
    return [...this.storage];
  }
}

class StudentService {
  constructor(private readonly repo: StudentRepo) {}

  enroll(student: Student): Student {
    if (student.credits < 3) {
      throw new Error("Student must have at least 3 credits");
    }

    return this.repo.save(student);
  }
}

type Either<L, R> = Left<L, R> | Right<L, R>;

class Left<L, R> {
  readonly tag = "left";

  constructor(readonly value: L) {}

  map<U>(_fn: (value: R) => U): Either<L, U> {
    return new Left<L, U>(this.value);
  }

  flatMap<U>(_fn: (value: R) => Either<L, U>): Either<L, U> {
    return new Left<L, U>(this.value);
  }
}

class Right<L, R> {
  readonly tag = "right";

  constructor(readonly value: R) {}

  map<U>(fn: (value: R) => U): Either<L, U> {
    return new Right<L, U>(fn(this.value));
  }

  flatMap<U>(fn: (value: R) => Either<L, U>): Either<L, U> {
    return fn(this.value);
  }
}

const left = <L, R>(value: L): Either<L, R> => new Left<L, R>(value);
const right = <L, R>(value: R): Either<L, R> => new Right<L, R>(value);

const validateCredits = (student: Student): Either<string, Student> =>
  student.credits >= 3 ? right(student) : left("Student must have at least 3 credits");

const createStudent = (student: Student): Either<string, Student> =>
  right({
    ...student,
    name: student.name.trim(),
  });

const saveToDB =
  (repo: StudentRepo) =>
  (student: Student): Either<string, Student> =>
    right(repo.save(student));

function pipeEither<A, L, B>(ab: (value: A) => Either<L, B>): (value: A) => Either<L, B>;
function pipeEither<A, L, B, C>(
  ab: (value: A) => Either<L, B>,
  bc: (value: B) => Either<L, C>,
): (value: A) => Either<L, C>;
function pipeEither<A, L, B, C, D>(
  ab: (value: A) => Either<L, B>,
  bc: (value: B) => Either<L, C>,
  cd: (value: C) => Either<L, D>,
): (value: A) => Either<L, D>;
function pipeEither(...fns: Array<(value: any) => Either<any, any>>) {
  return (value: any) => fns.reduce((result, fn) => result.flatMap(fn), right(value));
}

function printEither<L, R>(label: string, result: Either<L, R>): void {
  if (result.tag === "left") {
    console.log(label, "ERROR:", result.value);
    return;
  }

  console.log(label, "SUCCESS:", result.value);
}

const oopRepo = new StudentRepo();
const oopService = new StudentService(oopRepo);

const fpRepo = new StudentRepo();
const fpEnroll = pipeEither(validateCredits, createStudent, saveToDB(fpRepo));

const validStudent: Student = { id: "S-001", name: " Alice ", credits: 4 };
const invalidStudent: Student = { id: "S-002", name: "Bob", credits: 2 };

console.log("Task 2");

try {
  console.log("OOP success:", oopService.enroll(validStudent));
} catch (error) {
  console.log("OOP success path should not fail:", error);
}

try {
  console.log("OOP fail:", oopService.enroll(invalidStudent));
} catch (error) {
  console.log("OOP fail ERROR:", (error as Error).message);
}

printEither("FP success", fpEnroll(validStudent));
printEither("FP fail", fpEnroll(invalidStudent));

console.log("");
console.log("Answers");
console.log("1. Yes. In OOP, mutable objects can move through methods and invalid state can appear before checks or after partial changes.");
console.log("2. FP controls errors by wrapping every step in Either, so failure stops the pipeline without throwing exceptions.");
console.log("3. See mermaid.md for the sequence diagram and pipe flow diagram.");
