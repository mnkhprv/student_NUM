// LibraryController.ts
import { BorrowBookService } from "../../business/services/BorrowBookService";
import { ReturnBookService } from "../../business/services/ReturnBookService";

export class LibraryController {
  constructor(
    private borrowSvc: BorrowBookService,
    private returnSvc: ReturnBookService,
  ) {}

  async borrow(req: { memberId: string; isbn: string }) {
    if (!req.memberId || !req.isbn) {
      return { status: 400, body: { error: "missing fields" } };
    }

    try {
      return { status: 200, body: await this.borrowSvc.execute(req.memberId, req.isbn) };
    } catch (e: any) {
      return { status: 400, body: { error: e.message } };
    }
  }

  async returnBook(req: { copyId: string }) {
    if (!req.copyId) {
      return { status: 400, body: { error: "missing fields" } };
    }

    try {
      return { status: 200, body: await this.returnSvc.execute(req.copyId) };
    } catch (e: any) {
      return { status: 400, body: { error: e.message } };
    }
  }
}
