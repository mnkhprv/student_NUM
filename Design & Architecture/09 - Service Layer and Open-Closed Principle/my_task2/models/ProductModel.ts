export interface Product {
  id: number;
  name: string;
  price: number;
}

export const products: Product[] = [
  { id: 1, name: "Notebook", price: 1500 },
  { id: 2, name: "Smartphone", price: 800 },
  { id: 3, name: "Tablet", price: 600 },
];