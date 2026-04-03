abstract class BankAccount {
  constructor(
    public accountNumber: string,
    public owner: string,
    protected balance: number
  ) {}

  deposit(amount: number): void {
    if (amount <= 0) {
      console.log("Байршуулах мөнгөн дүн 0-ээс их байх ёстой.");
      return;
    }

    this.balance += amount;
    console.log(`${amount}₮ амжилттай байршууллаа. Шинэ үлдэгдэл: ${this.balance}₮`);
  }

  abstract withdraw(amount: number): void;

  getAccountInfo(): string {
    return `Дансны дугаар: ${this.accountNumber}, Эзэмшигч: ${this.owner}, Үлдэгдэл: ${this.balance}₮`;
  }

  getBalance(): number {
    return this.balance;
  }
}

class SavingsAccount extends BankAccount {
  withdraw(amount: number): void {
    if (amount <= 0) {
      console.log("Зарлагадах мөнгөн дүн 0-ээс их байх ёстой.");
      return;
    }

    if (this.balance - amount < 1000) {
      console.log(
        `Гүйлгээ амжилтгүй. Хадгаламжийн данс 1000₮-өөс бага үлдэгдэлтэй байж болохгүй. Одоогийн үлдэгдэл: ${this.balance}₮`
      );
      return;
    }

    this.balance -= amount;
    console.log(`${amount}₮ амжилттай зарлагадлаа. Шинэ үлдэгдэл: ${this.balance}₮`);
  }

  calculateInterest(rate: number): number {
    if (rate < 0) {
      console.log("Хүүгийн хувь сөрөг байж болохгүй.");
      return 0;
    }

    const interest = this.balance * (rate / 100);
    return interest;
  }

  override getAccountInfo(): string {
    return `[SavingsAccount] ${super.getAccountInfo()}`;
  }
}

class CheckingAccount extends BankAccount {
  constructor(
    accountNumber: string,
    owner: string,
    balance: number,
    public overdraftLimit: number
  ) {
    super(accountNumber, owner, balance);
  }

  withdraw(amount: number): void {
    if (amount <= 0) {
      console.log("Зарлагадах мөнгөн дүн 0-ээс их байх ёстой.");
      return;
    }

    if (this.balance - amount < -this.overdraftLimit) {
      console.log(
        `Гүйлгээ амжилтгүй. Зээлийн хязгаараас хэтэрлээ. Овердрафтын хязгаар: ${this.overdraftLimit}₮, Одоогийн үлдэгдэл: ${this.balance}₮`
      );
      return;
    }

    this.balance -= amount;
    console.log(`${amount}₮ амжилттай зарлагадлаа. Шинэ үлдэгдэл: ${this.balance}₮`);
  }

  override getAccountInfo(): string {
    return `[CheckingAccount] ${super.getAccountInfo()}, Overdraft limit: ${this.overdraftLimit}₮`;
  }
}

const savings = new SavingsAccount("SA1", "Munkhpurev", 5000);
const checking = new CheckingAccount("CA1", "Batbold", 3000, 2000);

console.log("ДАНС ҮҮСГЭХ");
console.log("Savings account үүслээ.");
console.log("Checking account үүслээ.");

console.log("\nДАНСНЫ МЭДЭЭЛЭЛ");
console.log(savings.getAccountInfo());
console.log(checking.getAccountInfo());

console.log("\nМӨНГӨ БАЙРШУУЛАХ" );
savings.deposit(2000);
checking.deposit(1000);

console.log("\nМӨНГӨ ЗАРЛАГАДАХ");
savings.withdraw(5500); // 7000 -> 1500, амжилттай
savings.withdraw(700);  // 1500 -> 800, болохгүй

checking.withdraw(4000); // 4000 -> 0, амжилттай
checking.withdraw(1500); // 0 -> -1500, амжилттай
checking.withdraw(1000); // -1500 -> -2500, болохгүй (limit 2000)

console.log("\nЖИЛИЙН ХҮҮ ТООЦОХ");
const interest = savings.calculateInterest(12);
console.log(`SavingsAccount жилийн хүү (12%): ${interest}₮`);

console.log("\nOVERDRAFT LIMIT ШАЛГАХ");
console.log(`CheckingAccount overdraft limit: ${checking.overdraftLimit}₮`);

console.log("\nЭЦСИЙН ДАНСНЫ МЭДЭЭЛЭЛ");
console.log(savings.getAccountInfo());
console.log(checking.getAccountInfo());