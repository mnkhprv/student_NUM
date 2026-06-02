export class Loan {
  readonly borrowedAt: Date;
  private _returnedAt: Date | null;

  constructor(
    readonly id: string,
    readonly memberId: string,
    readonly copyId: string,
    borrowedAt: Date = new Date(),
    returnedAt: Date | null = null,
  ) {
    this.borrowedAt = borrowedAt;
    this._returnedAt = returnedAt;
  }

  get returnedAt(): Date | null {
    return this._returnedAt;
  }

  get isActive(): boolean {
    return this._returnedAt === null;
  }

  markReturned(at: Date = new Date()): void {
    if (!this.isActive) {
      throw new Error("Loan already returned");
    }

    this._returnedAt = at;
  }
}
