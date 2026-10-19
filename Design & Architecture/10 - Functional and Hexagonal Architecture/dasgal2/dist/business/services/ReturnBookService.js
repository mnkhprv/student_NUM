"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ReturnBookService = void 0;
class ReturnBookService {
    constructor(copies, loans) {
        this.copies = copies;
        this.loans = loans;
    }
    async execute(copyId) {
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
exports.ReturnBookService = ReturnBookService;
