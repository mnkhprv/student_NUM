import { Task } from "../domain/Task";
import { Student } from "../domain/Student";
import { StudentService } from './StudentService';
import { error } from "node:console";

export class TaskService {
  constructor(
    private tasks: Task[],
    private studentService: StudentService
  ){}

  addTask(task: Task ): void  {
    this.tasks.push(task);
  }

  completeTask(taskId: string, studentId: string): void {
    const task = this.tasks.find(t => t.id === taskId);
    if (task) {
      task.completeTask(studentId);
    } else {
      throw new Error('Daalgavar oldsongui!')
    }
  }

  getTasksByCourse(courseId: string): Task[]  {
    return this.tasks.filter( t => t.courseId === courseId )
  }

  getCompletedStudents(taskId: string): Student[] {
    const task = this.tasks.find(t => t.id === taskId);
    if (!task) throw new Error('Daalgavar baihgui!');
    
    return task.completedBy
    .map(id => this.studentService.findStudentById(id))
    .filter((s): s is Student => s !== undefined);
  }
}