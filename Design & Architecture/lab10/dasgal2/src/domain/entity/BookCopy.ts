import { CopyStatus } from "./CopyStatus";

export class BookCopy {
  constructor(readonly id: string, readonly isbn: string, private _st: CopyStatus = "AVAILABLE") {}

  get status(): CopyStatus {
    return this._st;
  }

  markLoaned(): void {
    if (this._st !== "AVAILABLE") {
      throw new Error("Not available");
    }

    this._st = "LOANED";
  }

  markReturned(): void {
    if (this._st !== "LOANED") {
      throw new Error("Not loaned");
    }

    this._st = "AVAILABLE";
  }
}
