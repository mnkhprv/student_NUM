"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.InMemoryLoanRepo = exports.InMemoryCopyRepo = exports.InMemoryMemberRepo = void 0;
function isSameLocalDate(left, right) {
    return (left.getFullYear() === right.getFullYear() &&
        left.getMonth() === right.getMonth() &&
        left.getDate() === right.getDate());
}
class InMemoryMemberRepo {
    constructor(map = new Map()) {
        this.map = map;
    }
    seed(member) {
        this.map.set(member.id, member);
    }
    findById(id) {
        return Promise.resolve(this.map.get(id) ?? null);
    }
}
exports.InMemoryMemberRepo = InMemoryMemberRepo;
class InMemoryCopyRepo {
    constructor(map = new Map()) {
        this.map = map;
    }
    seed(copy) {
        this.map.set(copy.id, copy);
    }
    findAvailable(isbn) {
        return Promise.resolve([...this.map.values()].find((copy) => copy.isbn === isbn && copy.status === "AVAILABLE") ?? null);
    }
    findById(id) {
        return Promise.resolve(this.map.get(id) ?? null);
    }
    save(copy) {
        this.map.set(copy.id, copy);
        return Promise.resolve();
    }
}
exports.InMemoryCopyRepo = InMemoryCopyRepo;
class InMemoryLoanRepo {
    constructor() {
        this.map = new Map();
    }
    countActive(memberId) {
        return Promise.resolve([...this.map.values()].filter((loan) => loan.memberId === memberId && loan.isActive).length);
    }
    countBorrowedOn(memberId, date) {
        return Promise.resolve([...this.map.values()].filter((loan) => loan.memberId === memberId && isSameLocalDate(loan.borrowedAt, date)).length);
    }
    findActiveByCopy(copyId) {
        return Promise.resolve([...this.map.values()].find((loan) => loan.copyId === copyId && loan.isActive) ?? null);
    }
    save(loan) {
        this.map.set(loan.id, loan);
        return Promise.resolve();
    }
    update(loan) {
        this.map.set(loan.id, loan);
        return Promise.resolve();
    }
}
exports.InMemoryLoanRepo = InMemoryLoanRepo;
