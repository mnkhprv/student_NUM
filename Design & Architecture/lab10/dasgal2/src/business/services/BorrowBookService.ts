// BorrowBookService.ts
import { MemberRepo, CopyRepo, LoanRepo, Loan } from "../../domain";

export class BorrowBookService {
  private static readonly DAILY_BORROW_LIMIT = 2;

  constructor(
    private members: MemberRepo,
    private copies: CopyRepo,
    private loans: LoanRepo,
  ) {}

  async execute(memberId: string, isbn: string): Promise<{ loanId: string; copyId: string }> {
    const member = await this.members.findById(memberId);
    if (!member) {
      throw new Error("Member not found");
    }

    const activeLoans = await this.loans.countActive(memberId);
    if (!member.canBorrow(activeLoans)) {
      throw new Error("Loan limit reached");
    }

    const borrowedToday = await this.loans.countBorrowedOn(memberId, new Date());
    if (borrowedToday >= BorrowBookService.DAILY_BORROW_LIMIT) {
      throw new Error("Daily borrow limit reached");
    }

    const copy = await this.copies.findAvailable(isbn);
    if (!copy) {
      throw new Error("No available copy");
    }

    copy.markLoaned();
    const loan = new Loan(this.nextLoanId(memberId, copy.id), memberId, copy.id);

    await this.copies.save(copy);
    await this.loans.save(loan);

    return { loanId: loan.id, copyId: copy.id };
  }

  private nextLoanId(memberId: string, copyId: string): string {
    return `LN-${memberId}-${copyId}-${Date.now()}`;
  }
}
