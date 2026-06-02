"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Loan = void 0;
class Loan {
    constructor(id, memberId, copyId, borrowedAt = new Date(), returnedAt = null) {
        this.id = id;
        this.memberId = memberId;
        this.copyId = copyId;
        this.borrowedAt = borrowedAt;
        this._returnedAt = returnedAt;
    }
    get returnedAt() {
        return this._returnedAt;
    }
    get isActive() {
        return this._returnedAt === null;
    }
    markReturned(at = new Date()) {
        if (!this.isActive) {
            throw new Error("Loan already returned");
        }
        this._returnedAt = at;
    }
}
exports.Loan = Loan;
