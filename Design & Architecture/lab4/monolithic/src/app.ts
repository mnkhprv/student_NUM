interface Age {
  getAge(): number;
}

class Car implements Age {
  constructor(
    public model: string,
    public color: string,
    public year: number
  ) {}

  getAge(): number {
    return new Date().getFullYear() - this.year;
  }
}

class Person implements Age {
  constructor(
    public name: string,
    public birthYear: number,
    public car: Car
  ) {}

  getAge(): number {
    return new Date().getFullYear() - this.birthYear;
  }
}

class Building implements Age {
  constructor(
    public name: string,
    public builtYear: number
  ) {}

  getAge(): number {
    return new Date().getFullYear() - this.builtYear;
  }
}

class CarStatusService {
  getCarStatus(year: number): string {
    const age = new Date().getFullYear() - year;

    if (age > 10) {
      return "насжилттай";
    } else if (age === 1) {
      return "шинэ";
    } else {
      return "он залуу";
    }
  }
}

class PersonCarSystem {
  private statusService: CarStatusService;

  constructor() {
    this.statusService = new CarStatusService();
  }

  showPersonCarInfo(person: Person): void {
    const status = this.statusService.getCarStatus(person.car.year);

    console.log("=== Хүний машины мэдээлэл ===");
    console.log(`Нэр: ${person.name}`);
    console.log(`Хүний нас: ${person.getAge()}`);
    console.log(`Машины загвар: ${person.car.model}`);
    console.log(`Өнгө: ${person.car.color}`);
    console.log(`Үйлдвэрлэсэн он: ${person.car.year}`);
    console.log(`Машины нас: ${person.car.getAge()}`);
    console.log(`Төлөв: ${status}`);
  }
}

function showAgeInfo(itemName: string, item: Age): void {
  console.log(`${itemName}-ийн нас: ${item.getAge()}`);
}

// Ашиглалт
const car1 = new Car("Toyota Prius", "Цагаан", 2012);
const person1 = new Person("Мөнхпүрэв", 2002, car1);
const building1 = new Building("Blue Sky Tower", 2009);

const system = new PersonCarSystem();
system.showPersonCarInfo(person1);

console.log("=== Age interface implement хийсэн жишээ ===");
showAgeInfo("Хүн", person1);
showAgeInfo("Машин", car1);
showAgeInfo("Барилга", building1);
