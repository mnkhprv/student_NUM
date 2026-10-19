"use strict";
class StudentList {
    constructor(names) {
        this.names = names;
    }
    filterLongNames(minLength) {
        return this.names.filter((name) => name.length > minLength);
    }
    toUpperCase(names) {
        return names.map((name) => name.toUpperCase());
    }
}
function pipe(...fns) {
    return (value) => fns.reduce((current, fn) => fn(current), value);
}
const filterLongNames = (minLength) => (names) => names.filter((name) => name.length > minLength);
const toUpperCase = (names) => names.map((name) => name.toUpperCase());
const students = ["Bat", "Dorj", "Suren"];
const oopStudentList = new StudentList(students);
const oopResult = oopStudentList.toUpperCase(oopStudentList.filterLongNames(4));
const fpTransform = pipe(filterLongNames(4), toUpperCase);
const fpResult = fpTransform(students);
console.log("Task 1");
console.log("OOP result:", oopResult);
console.log("FP result:", fpResult);
console.log("");
console.log("Answers");
console.log("1. FP reduces coupling more because each transformation is an independent pure function.");
console.log("2. OOP keeps state in StudentList through the names field. FP works with input/output values only.");
