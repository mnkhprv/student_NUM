import { BaseService } from "./BaseService";
import { Product, products } from "../models/ProductModel";

export class ProductService extends BaseService<Product> {
  constructor() {
    super(products);
  }

  // Open/Closed Principle жишээ: BaseService-г өөрчлөхгүйгээр шинэ функц нэмэв
  getExpensiveProducts(): Product[] {
    return this.items.filter((p) => p.price > 1000);
  }
}