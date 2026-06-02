import { CopyRepo, LoanRepo } from "../../domain";

export class ReturnBookService {
  constructor(
    private copies: CopyRepo,
    private loans: LoanRepo,
  ) {}

  async execute(copyId: string): Promise<{ copyId: string; returned: true }> {
    const copy = await this.copies.findById(copyId);
    if (!copy) {
      throw new Error("Copy not found");
    }

    const loan = await this.loans.findActiveByCopy(copyId);
    if (!loan) {
      throw new Error("Active loan not found");
    }

    copy.markReturned();
    loan.markReturned();

    await this.copies.save(copy);
    await this.loans.update(loan);

    return { copyId: copy.id, returned: true };
  }
}
