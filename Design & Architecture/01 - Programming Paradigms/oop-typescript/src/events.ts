import { EventEmitter } from 'events';
import { cart, Item } from './data';

class CartEvents extends EventEmitter {}
const bus = new CartEvents();

// Хэрэглэх
bus.on('ITEM_ADDED', (it: Item) => console.log('Нэмэгдсэн:', it.name));
bus.on('CHECKOUT', (total: number) => console.log('Нийт checkout:', total));
bus.on('QUANTITY_CHANGED', (data) => {
  const direction = data.newQty > data.oldQty ? 'Нэмэгдлээ' : 'Хасагдлаа';
  console.log(`${data.name}-ийн тоо ширхэг ${data.newQty} болж ${direction}`)
});

// энгийн cart “модуль”
let items: Item[] = [...cart];

function addItem(it: Item) {
  items = [...items, it];
  bus.emit('ITEM_ADDED', it);
}

function changeQuality( name: string, newQty: number){
  const item = items.find(i => i.name === name);
  if(item) {
    const oldQty = item.qty;
    items = items.map( i => 
      i.name === name ? { ...i, qty: newQty } : i
    )

    bus.emit('QUANTITY_CHANGED', { 
      name: item.name, 
      oldQty: oldQty, 
      newQty: newQty 
    });
  }
}

function checkout() {
  const total = items.reduce((s, i) => s + i.price * i.qty, 0);
  bus.emit('CHECKOUT', total);
  return total;
}

// ажиллуулах
addItem({ name: 'Chocolate', price: 4200, qty: 3, category: 'food' });
checkout();
changeQuality( 'Chocolate', 5);
checkout();
