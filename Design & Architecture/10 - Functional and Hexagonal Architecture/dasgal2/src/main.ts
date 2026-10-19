// src/main.ts
import { InMemoryMemberRepo, InMemoryCopyRepo, InMemoryLoanRepo } from './infrastructure/repositories/in-memory/InMemoryRepos';
import { LibraryController } from './presentation/controllers/LibraryController';
import { BorrowBookService } from './business/services/BorrowBookService';
import { ReturnBookService } from './business/services/ReturnBookService';
import { Member, BookCopy } from './domain';

// ============================
// 1. Infrastructure
// ============================
const memberRepo = new InMemoryMemberRepo();
const copyRepo   = new InMemoryCopyRepo();
const loanRepo   = new InMemoryLoanRepo();

// ============================
// 2. Seed data
// ============================
const member = new Member("M001");
memberRepo.seed(member);

const bookCopy1 = new BookCopy("C001", "ISBN-111");
const bookCopy2 = new BookCopy("C002", "ISBN-111");
copyRepo.seed(bookCopy1);
copyRepo.seed(bookCopy2);

// ============================
// 3. Business Layer
// ============================
const borrowService = new BorrowBookService(memberRepo, copyRepo, loanRepo);
const returnService = new ReturnBookService(copyRepo, loanRepo);

// ============================
// 4. Presentation Layer
// ============================
const controller = new LibraryController(borrowService, returnService);

// ============================
// 5. Тест
// ============================
async function run() {
  console.log("📚 Library system starting...\n");

  const result1 = await controller.borrow({ memberId: "M001", isbn: "ISBN-111" });
  console.log("✅ First borrow:", result1);

  const result2 = await controller.borrow({ memberId: "M001", isbn: "ISBN-111" });
  console.log("✅ Second borrow:", result2);

  const returnResult = await controller.returnBook({ copyId: "C001" });
  console.log("↩️ Returned:", returnResult);

  const result3 = await controller.borrow({ memberId: "M001", isbn: "ISBN-111" });
  console.log("🚫 Third borrow after return:", result3);

  console.log("\n🎉 Амжилттай! Одоо Дасгал 2 хийхэд бэлэн.");
}

run().catch(console.error);
