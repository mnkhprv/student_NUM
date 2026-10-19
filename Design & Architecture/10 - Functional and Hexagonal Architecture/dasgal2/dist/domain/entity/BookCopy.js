"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.BookCopy = void 0;
class BookCopy {
    constructor(id, isbn, _st = "AVAILABLE") {
        this.id = id;
        this.isbn = isbn;
        this._st = _st;
    }
    get status() {
        return this._st;
    }
    markLoaned() {
        if (this._st !== "AVAILABLE") {
            throw new Error("Not available");
        }
        this._st = "LOANED";
    }
    markReturned() {
        if (this._st !== "LOANED") {
            throw new Error("Not loaned");
        }
        this._st = "AVAILABLE";
    }
}
exports.BookCopy = BookCopy;
