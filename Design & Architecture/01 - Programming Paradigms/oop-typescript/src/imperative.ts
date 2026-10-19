import { cart, Item } from './data';
function totalFood(items: Item[]): number {
  let sum = 0;
  for (let i = 0; i < items.length; i++) {
    const it = items[i];
    if (it.category === 'food') {
      sum += it.price * it.qty;
    } 
  }
  return sum;
}

function mostExpensive(items: Item[]): Item | null {
  if (items.length === 0) return null;
  let max = items[0];
  for (let i = 1; i < items.length; i++) {
    if (items[i].price > max.price) max = items[i];
  }
  return max;
}

function applyVipIfNeeded(total: number): number {
  if (total > 100_000) return Math.round(total * 0.95);
  return total;
}

// “процедур” урсгал:
const foodSum = totalFood(cart);
const grandTotal = cart.reduce((s, it) => s + it.price * it.qty, 0);
const maxItem = mostExpensive(cart);
const finalTotal = applyVipIfNeeded(grandTotal);
console.log({ foodSum, maxItem: maxItem?.name, grandTotal, finalTotal });