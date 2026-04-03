export class Task {

  completedBy: string[] = [];

  constructor(
    public id : string,
    public title : string,
    public courseId : string
  ){}

  completeTask = (studentId: string): void => {
    if (!this.completedBy.includes(studentId)){
      this.completedBy.push(studentId);
    }
  }
}