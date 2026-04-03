import { Item, cart } from './data';
class ShoppingCart {
  #items: Item[] = [];
  constructor(items: Item[] = []) { this.#items = [...items]; } // иммутабилити-Дотроо өөрчлөх бус гаднаас өөрчлөх
  add(item: Item) { this.#items = [...this.#items, item]; }
  get items(): readonly Item[] { return this.#items; }
  totalFood() {
    return this.#items
    .filter(i => i.category === 'food')
    .reduce((s, i) => s + i.price * i.qty, 0);
  }
  mostExpensive(): Item | null {
    return this.#items.reduce((m: Item | null, c) => (m && m.price > c.price ? m : c), null);
  }
  grandTotal() {
    return this.#items.reduce((s, i) => s + i.price * i.qty, 0);
  }
  finalTotal() {
    const total = this.grandTotal();
    return total > 100_000 ? Math.round(total * 0.95) : total;
  }
}
const sc = new ShoppingCart(cart);
console.log({
 foodSum: sc.totalFood(),
 maxItem: sc.mostExpensive()?.name,
 grandTotal: sc.grandTotal(),
 finalTotal: sc.finalTotal(),
});