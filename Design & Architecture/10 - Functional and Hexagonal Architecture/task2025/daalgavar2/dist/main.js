"use strict";
class StudentRepo {
    constructor() {
        this.storage = [];
    }
    save(student) {
        this.storage.push(student);
        return student;
    }
    all() {
        return [...this.storage];
    }
}
class StudentService {
    constructor(repo) {
        this.repo = repo;
    }
    enroll(student) {
        if (student.credits < 3) {
            throw new Error("Student must have at least 3 credits");
        }
        return this.repo.save(student);
    }
}
class Left {
    constructor(value) {
        this.value = value;
        this.tag = "left";
    }
    map(_fn) {
        return new Left(this.value);
    }
    flatMap(_fn) {
        return new Left(this.value);
    }
}
class Right {
    constructor(value) {
        this.value = value;
        this.tag = "right";
    }
    map(fn) {
        return new Right(fn(this.value));
    }
    flatMap(fn) {
        return fn(this.value);
    }
}
const left = (value) => new Left(value);
const right = (value) => new Right(value);
const validateCredits = (student) => student.credits >= 3 ? right(student) : left("Student must have at least 3 credits");
const createStudent = (student) => right({
    ...student,
    name: student.name.trim(),
});
const saveToDB = (repo) => (student) => right(repo.save(student));
function pipeEither(...fns) {
    return (value) => fns.reduce((result, fn) => result.flatMap(fn), right(value));
}
function printEither(label, result) {
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
const validStudent = { id: "S-001", name: " Alice ", credits: 4 };
const invalidStudent = { id: "S-002", name: "Bob", credits: 2 };
console.log("Task 2");
try {
    console.log("OOP success:", oopService.enroll(validStudent));
}
catch (error) {
    console.log("OOP success path should not fail:", error);
}
try {
    console.log("OOP fail:", oopService.enroll(invalidStudent));
}
catch (error) {
    console.log("OOP fail ERROR:", error.message);
}
printEither("FP success", fpEnroll(validStudent));
printEither("FP fail", fpEnroll(invalidStudent));
console.log("");
console.log("Answers");
console.log("1. Yes. In OOP, mutable objects can move through methods and invalid state can appear before checks or after partial changes.");
console.log("2. FP controls errors by wrapping every step in Either, so failure stops the pipeline without throwing exceptions.");
console.log("3. See mermaid.md for the sequence diagram and pipe flow diagram.");
