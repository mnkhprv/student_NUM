"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.BorrowBookService = void 0;
// BorrowBookService.ts
const domain_1 = require("../../domain");
class BorrowBookService {
    constructor(members, copies, loans) {
        this.members = members;
        this.copies = copies;
        this.loans = loans;
    }
    async execute(memberId, isbn) {
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
        const loan = new domain_1.Loan(this.nextLoanId(memberId, copy.id), memberId, copy.id);
        await this.copies.save(copy);
        await this.loans.save(loan);
        return { loanId: loan.id, copyId: copy.id };
    }
    nextLoanId(memberId, copyId) {
        return `LN-${memberId}-${copyId}-${Date.now()}`;
    }
}
exports.BorrowBookService = BorrowBookService;
BorrowBookService.DAILY_BORROW_LIMIT = 2;
