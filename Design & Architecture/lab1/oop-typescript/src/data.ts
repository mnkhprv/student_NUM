export type Item = { 
  name: string; 
  price: number; 
  qty: number; 
  category: 'food'|'book'|'elec' 
};

export const cart: Item[] = [
 { name: 'Milk', price: 3500, qty: 2, category: 'food' },
 { name: 'Bread', price: 2800, qty: 1, category: 'food' },
 { name: 'Novel', price: 18000, qty: 1, category: 'book' },
 { name: 'Headset',price: 95000, qty: 1, category: 'elec' },
 { name: 'Apple', price: 1200, qty: 6, category: 'food' },
];