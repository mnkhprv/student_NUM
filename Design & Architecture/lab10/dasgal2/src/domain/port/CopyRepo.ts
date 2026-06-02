import { BookCopy } from "../entity/BookCopy";

export interface CopyRepo {
  findAvailable(isbn: string): Promise<BookCopy | null>;
  findById(id: string): Promise<BookCopy | null>;
  save(copy: BookCopy): Promise<void>;
}
