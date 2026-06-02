export class Member {
 constructor(readonly id: string, private readonly maxLoans = 5) {}
 canBorrow(activeLoans: number) { return activeLoans < this.maxLoans; }
}