import { cart } from './data';
// “food нийлбэр” — ямар үр дүн хүсэж байгаагаа л илэрхийлнэ
const foodSum =
  cart.filter(i => i.category === 'food')
  .map(i => i.price * i.qty)
  .reduce((a, b) => a + b, 0);
  
const grandTotal = cart.map(i => i.price * i.qty).reduce((a, b) => a + b, 0);
const maxItem = cart.reduce((m, c) => (m && m.price > c.price ? m : c), null as any);
const finalTotal = grandTotal > 100_000 ? Math.round(grandTotal * 0.95) : grandTotal;
console.log({ foodSum, grandTotal, max: maxItem?.name, finalTotal });