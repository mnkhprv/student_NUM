"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.LibraryController = void 0;
class LibraryController {
    constructor(borrowSvc, returnSvc) {
        this.borrowSvc = borrowSvc;
        this.returnSvc = returnSvc;
    }
    async borrow(req) {
        if (!req.memberId || !req.isbn) {
            return { status: 400, body: { error: "missing fields" } };
        }
        try {
            return { status: 200, body: await this.borrowSvc.execute(req.memberId, req.isbn) };
        }
        catch (e) {
            return { status: 400, body: { error: e.message } };
        }
    }
    async returnBook(req) {
        if (!req.copyId) {
            return { status: 400, body: { error: "missing fields" } };
        }
        try {
            return { status: 200, body: await this.returnSvc.execute(req.copyId) };
        }
        catch (e) {
            return { status: 400, body: { error: e.message } };
        }
    }
}
exports.LibraryController = LibraryController;
