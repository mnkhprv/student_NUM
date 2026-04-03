import { Furniture } from "../domain/Furniture";

export class CostCalculator {
  static calculateTotalMaterialUsage(furnitureList: Furniture[]): number {
    let totalUsage = 0;

    furnitureList.forEach((furniture) => {
      totalUsage += furniture.calculateMaterialUsage();
    });

    return totalUsage;
  }

  static calculateTotalCost(furnitureList: Furniture[]): number {
    let totalCost = 0;

    furnitureList.forEach((furniture) => {
      totalCost += furniture.getMaterialCost();
    });

    return totalCost;
  }
}
