class Customer {
  constructor(
    public readonly id: string,
    public readonly name: string,
    private readonly loyaltyRate: number,
    private readonly specialDiscount: number
  ) {}

  getDiscountInfo() {
    return {
      loyaltyRate: this.loyaltyRate,
      specialDiscount: this.specialDiscount,
    };
  }
}

class Product {
  constructor(
    public readonly id: string,
    public readonly name: string,
    private readonly unitPrice: number,
    private readonly currency: string = "USD"
  ) {}

  getPricingDetails() {
    return {
      unitPrice: this.unitPrice,
      currency: this.currency,
    };
  }
}

class OrderLine {
  constructor(
    public readonly id: string,
    private readonly quantity: number,
    private readonly product: Product
  ) {}

  getQuantity(): number {
    return this.quantity;
  }

  getProduct(): Product {
    return this.product;
  }
}

class Order {
  constructor(public readonly id: string) {}

  calculatePrice(orderLine: OrderLine, customer: Customer): number {

    const quantity = orderLine.getQuantity();
    const product = orderLine.getProduct();
    const pricingDetails = product.getPricingDetails();

    const basePrice = this.calculateBasePrice(
      pricingDetails.unitPrice,
      quantity
    );
    const totalDiscount = this.calculateDiscounts(customer, basePrice);
    const finalPrice = Math.max(basePrice - totalDiscount, 0);
    return finalPrice;
  }

  private calculateBasePrice(unitPrice: number, quantity: number): number {
    return unitPrice * quantity;
  }

  private calculateDiscounts(customer: Customer, basePrice: number): number {
    const discountInfo = customer.getDiscountInfo();
    return discountInfo.specialDiscount;
  }
}
