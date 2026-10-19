"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Member = void 0;
class Member {
    constructor(id, maxLoans = 5) {
        this.id = id;
        this.maxLoans = maxLoans;
    }
    canBorrow(activeLoans) { return activeLoans < this.maxLoans; }
}
exports.Member = Member;
