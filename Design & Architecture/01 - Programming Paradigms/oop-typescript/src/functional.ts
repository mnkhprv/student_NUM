import { cart, Item } from './data';
// 1) food нийлбэр (цэвэр функц)
export const totalFood = (items: readonly Item[]) =>
  items
  .filter(i => i.category === 'food')
  .map(i => i.price * i.qty)
  .reduce((a, b) => a + b, 0);

  // 2) хамгийн үнэтэй (гадны төлөв өөрчлөхгүй)
export const mostExpensive = (items: readonly Item[]) =>
  items.reduce((max: Item | null, cur) => (max && max.price > cur.price ? max : cur), null);

// 3) VIP хөнгөлөлт (тасархай округлалтгүйгээр жишээ)
export const applyVipIfNeeded = (total: number) => (total > 100_000 ? Math.round(total * 0.95) :
total);

// нийлбэр:
const grandTotal = cart.map(i => i.price * i.qty).reduce((a, b) => a + b, 0);

// гаралт
console.log({
 foodSum: totalFood(cart),
 maxItem: mostExpensive(cart)?.name,
 grandTotal,
 finalTotal: applyVipIfNeeded(grandTotal),
});