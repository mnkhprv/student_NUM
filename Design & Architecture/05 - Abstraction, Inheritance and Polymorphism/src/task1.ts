interface Bookable {
  book(): void;
  cancel(): void;
  getDetails(): string;
}

abstract class Trip {
  constructor(
    public destination: string,
    public price: number
  ){}

  getSummary(): string {
    return `Очих газар: ${this.destination}, Үнэ: $${this.price}`;
  }

  abstract book(): void;
  abstract cancel(): void;
}

class FlightTrip extends Trip implements Bookable {
  constructor(
    destination: string,
    price: number,
    public airline: string
  ){
    super(destination, price);
  }

  book() : void {
    console.log(`${this.destination} чиглэлийн нислэг амжилттай захиалагдлаа.`);
  }
  cancel(): void {
    console.log(`${this.destination} чиглэлийн нислэгийн захиалга цуцлагдлаа.`);
  }
  getDetails(): string {
    return `Нислэгийн аялал -> ${this.getSummary()}, Нисэх компани: ${this.airline}`;
  }  
}


class CruiseTrip extends Trip implements Bookable {
  constructor(
    destination: string,
    price: number,
    public shipName: string
  ){
    super(destination, price);
  }
  book(): void {
    console.log(`${this.destination} чиглэлийн далайн аялал амжилттай захиалагдлаа.`);
  }

  cancel(): void {
    console.log(`${this.destination} чиглэлийн далайн аяллын захиалга цуцлагдлаа.`);
  }

  getDetails(): string {
    return `Далайн аялал -> ${this.getSummary()}, Усан онгоц: ${this.shipName}`;
  }  
}

class TrainTrip extends Trip implements Bookable {
  constructor(
    destination: string,
    price: number,
    public trainName: string
  ) {
    super(destination, price);
  }

  book(): void {
    console.log(`${this.destination} чиглэлийн галт тэрэгний аялал захиалагдлаа.`);
  }

  cancel(): void {
    console.log(`${this.destination} чиглэлийн галт тэрэгний аяллын захиалга цуцлагдлаа.`);
  }

  getDetails(): string {
    return `Галт тэрэгний аялал -> ${this.getSummary()}, Галт тэрэг: ${this.trainName}`;
  }
}

class HikingTrip extends Trip implements Bookable {
  constructor(
    destination: string,
    price: number,
    public guideName: string
  ) {
    super(destination, price);
  }

  book(): void {
    console.log(`${this.destination} чиглэлийн явган аялал захиалагдлаа.`);
  }

  cancel(): void {
    console.log(`${this.destination} чиглэлийн явган аяллын захиалга цуцлагдлаа.`);
  }

  getDetails(): string {
    return `Явган аялал -> ${this.getSummary()}, Хөтөч: ${this.guideName}`;
  }
}

const flight1 = new FlightTrip("Seoul", 450, "Korean Air");
const cruise1 = new CruiseTrip("Caribbean", 1200, "Ocean Dream");
const train1 = new TrainTrip("Beijing", 300, "TransAsia Express");
const hiking1 = new HikingTrip("Altai Tavan Bogd", 150, "Bat-Erdene");

flight1.book();
console.log(flight1.getDetails());
flight1.cancel();

cruise1.book();
console.log(cruise1.getDetails());
cruise1.cancel();

train1.book();
console.log(train1.getDetails());
train1.cancel();

hiking1.book();
console.log(hiking1.getDetails());
hiking1.cancel();