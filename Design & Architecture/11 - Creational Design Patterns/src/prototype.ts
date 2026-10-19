// 1. Prototype интерфейсийг тодорхойлох: Объект хуулбарлах үйлдлийг зааж өгдөг.
interface Prototype<T> {
 clone(): T;
}
// 2. Book класс нь Prototype интерфейсийг хэрэгжүүлнэ.
class Book implements Prototype<Book> {
 constructor(
 public title: string,
 public author: string,
 public year: number
 ) {}

  // clone функц: Одоогийн объект дээр үндэслэн шинэ Book объект үүсгэж буцаана.
 clone(): Book {
 // Шаардлагатай бол гүн хуулбар (deep copy) логикыг оруулах боломжтой.

  return new Book(this.title, this.author, this.year);
 }
}
// 3. Объект үүсгэх ба хуулбарлах үйлдэл:
const originalBook = new Book("Монголын Түүх", "Г. Бат", 2020);
const clonedBook = originalBook.clone();
// Лог хийж шалгах:
console.log("Эх book объект:", originalBook);
console.log("Хуулагдсан book объект:", clonedBook);
// Объектууд ижил утгатай ч өөр өөр санах ойд байрлана:
console.log("Эх объект болон хуулбар ижил үү?", originalBook === clonedBook); // false