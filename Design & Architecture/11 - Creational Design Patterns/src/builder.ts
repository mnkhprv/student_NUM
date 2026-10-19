// 1. Product: Компьютер
class Computer {
 public cpu: string = "";
 public ram: string = "";
 public storage: string = "";
 public graphicsCard: string = "";
 // Компьютерийн бүрэлдэхүүн хэсгүүдийг харуулах функц
 public displayConfig(): void {
 console.log(`CPU: ${this.cpu}`);
 console.log(`RAM: ${this.ram}`);
 console.log(`Хадгалах систем: ${this.storage}`);
 console.log(`График карт: ${this.graphicsCard}`);
 }
}

// 2. Builder Интерфейс: Компьютер Билдер
interface ComputerBuilder {
 setCPU(cpu: string): ComputerBuilder;
 setRAM(ram: string): ComputerBuilder;
 setStorage(storage: string): ComputerBuilder;
 setGraphicsCard(graphicsCard: string): ComputerBuilder;
 build(): Computer;
}
// 3. Concrete Builder: Гейминг Компьютер Билдер
class GamingComputerBuilder implements ComputerBuilder {
 private computer: Computer;
 constructor() {
 this.computer = new Computer();
 }

  public setCPU(cpu: string): ComputerBuilder {
 this.computer.cpu = cpu;
 return this;
 }
 public setRAM(ram: string): ComputerBuilder {
 this.computer.ram = ram;
 return this;
 }
 public setStorage(storage: string): ComputerBuilder {
 this.computer.storage = storage;
 return this;
 }
 public setGraphicsCard(graphicsCard: string): ComputerBuilder {
 this.computer.graphicsCard = graphicsCard;
 return this;
 }
 // Компьютер объектын үүсгэж буцаах
 public build(): Computer {
 return this.computer;
 }
}

// 4. Director: Компьютер Директор
class ComputerDirector {
 private builder: ComputerBuilder;
 constructor(builder: ComputerBuilder) {
 this.builder = builder;
 }
 // Директорын стандарт үйл явц: Гэминг зориулсан өндөр чанарын компьютер үүсгэх
 public buildHighEndGamingComputer(): Computer {
 return this.builder
 .setCPU("Intel Core i9")
 .setRAM("32GB")
 .setStorage("1TB SSD")
 .setGraphicsCard("NVIDIA RTX 3080")
 .build();
 }
}

// 5. Хэрэглэх жишээ:
// Билдерийг үүсгэх
const gamingBuilder = new GamingComputerBuilder();
// Директорыг үүсгэж, билдерийг дамжуулан өндөр чанарын компьютер бүтээнэ
const director = new ComputerDirector(gamingBuilder);
const highEndComputer = director.buildHighEndGamingComputer();
// Үүсгэсэн компьютерийн бүрэлдэхүүн хэсгүүдийг харуулах
highEndComputer.displayConfig();