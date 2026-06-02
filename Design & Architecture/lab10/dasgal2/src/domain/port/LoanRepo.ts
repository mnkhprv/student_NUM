import { Loan } from "../entity/Loan";

export interface LoanRepo {
  countActive(memberId: string): Promise<number>;
  countBorrowedOn(memberId: string, date: Date): Promise<number>;
  save(loan: Loan): Promise<void>;
  findActiveByCopy(copyId: string): Promise<Loan | null>;
  update(loan: Loan): Promise<void>;
}
