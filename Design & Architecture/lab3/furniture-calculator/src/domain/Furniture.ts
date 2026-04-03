import { Material } from "./Material";

export abstract class Furniture {
  constructor(
    public name: string,
    public material: Material,
    public requiredWidth: number,
    public requiredHeight: number
  ) {}

  abstract calculateMaterialUsage(): number;

  getMaterialCost(): number {
    return this.calculateMaterialUsage() * this.material.pricePerUnit;
  }
}

export class Chair extends Furniture {
  calculateMaterialUsage(): number {
    return this.requiredWidth * this.requiredHeight;
  }
}

export class Table extends Furniture {
  calculateMaterialUsage(): number {
    return this.requiredWidth * this.requiredHeight;
  }
}

export class Wardrobe extends Furniture {
  calculateMaterialUsage(): number {
    return this.requiredWidth * this.requiredHeight;
  }
}

export class Cabinet extends Furniture {
  calculateMaterialUsage(): number {
    return this.requiredWidth * this.requiredHeight;
  }
}
