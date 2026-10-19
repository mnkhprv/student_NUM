"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
// src/main.ts
const InMemoryRepos_1 = require("./infrastructure/repositories/in-memory/InMemoryRepos");
const LibraryController_1 = require("./presentation/controllers/LibraryController");
const BorrowBookService_1 = require("./business/services/BorrowBookService");
const ReturnBookService_1 = require("./business/services/ReturnBookService");
const domain_1 = require("./domain");
// ============================
// 1. Infrastructure
// ============================
const memberRepo = new InMemoryRepos_1.InMemoryMemberRepo();
const copyRepo = new InMemoryRepos_1.InMemoryCopyRepo();
const loanRepo = new InMemoryRepos_1.InMemoryLoanRepo();
// ============================
// 2. Seed data
// ============================
const member = new domain_1.Member("M001");
memberRepo.seed(member);
const bookCopy1 = new domain_1.BookCopy("C001", "ISBN-111");
const bookCopy2 = new domain_1.BookCopy("C002", "ISBN-111");
copyRepo.seed(bookCopy1);
copyRepo.seed(bookCopy2);
// ============================
// 3. Business Layer
// ============================
const borrowService = new BorrowBookService_1.BorrowBookService(memberRepo, copyRepo, loanRepo);
const returnService = new ReturnBookService_1.ReturnBookService(copyRepo, loanRepo);
// ============================
// 4. Presentation Layer
// ============================
const controller = new LibraryController_1.LibraryController(borrowService, returnService);
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
