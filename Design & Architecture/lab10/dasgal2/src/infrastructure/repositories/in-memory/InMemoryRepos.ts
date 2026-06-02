// InMemoryRepos.ts
import { MemberRepo, CopyRepo, LoanRepo, Member, BookCopy, Loan } from "../../../domain";

function isSameLocalDate(left: Date, right: Date): boolean {
  return (
    left.getFullYear() === right.getFullYear() &&
    left.getMonth() === right.getMonth() &&
    left.getDate() === right.getDate()
  );
}

export class InMemoryMemberRepo implements MemberRepo {
  constructor(private map = new Map<string, Member>()) {}

  seed(member: Member): void {
    this.map.set(member.id, member);
  }

  findById(id: string): Promise<Member | null> {
    return Promise.resolve(this.map.get(id) ?? null);
  }
}

export class InMemoryCopyRepo implements CopyRepo {
  constructor(private map = new Map<string, BookCopy>()) {}

  seed(copy: BookCopy): void {
    this.map.set(copy.id, copy);
  }

  findAvailable(isbn: string): Promise<BookCopy | null> {
    return Promise.resolve(
      [...this.map.values()].find((copy) => copy.isbn === isbn && copy.status === "AVAILABLE") ?? null,
    );
  }

  findById(id: string): Promise<BookCopy | null> {
    return Promise.resolve(this.map.get(id) ?? null);
  }

  save(copy: BookCopy): Promise<void> {
    this.map.set(copy.id, copy);
    return Promise.resolve();
  }
}

export class InMemoryLoanRepo implements LoanRepo {
  private map = new Map<string, Loan>();

  countActive(memberId: string): Promise<number> {
    return Promise.resolve(
      [...this.map.values()].filter((loan) => loan.memberId === memberId && loan.isActive).length,
    );
  }

  countBorrowedOn(memberId: string, date: Date): Promise<number> {
    return Promise.resolve(
      [...this.map.values()].filter(
        (loan) => loan.memberId === memberId && isSameLocalDate(loan.borrowedAt, date),
      ).length,
    );
  }

  findActiveByCopy(copyId: string): Promise<Loan | null> {
    return Promise.resolve(
      [...this.map.values()].find((loan) => loan.copyId === copyId && loan.isActive) ?? null,
    );
  }

  save(loan: Loan): Promise<void> {
    this.map.set(loan.id, loan);
    return Promise.resolve();
  }

  update(loan: Loan): Promise<void> {
    this.map.set(loan.id, loan);
    return Promise.resolve();
  }
}
