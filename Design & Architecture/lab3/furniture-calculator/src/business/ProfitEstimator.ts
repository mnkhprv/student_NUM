import { Furniture } from "../domain/Furniture";
import { CostCalculator } from "./CostCalculator";

export class ProfitEstimator {
  static estimateProfit(
    furnitureList: Furniture[],
    sellingPricePerUnit: number,
    durationInMonths: number,
    monthlyGrowthRate = 0.02
  ): number {
    const totalCost = CostCalculator.calculateTotalCost(furnitureList);
    const totalRevenue = furnitureList.length * sellingPricePerUnit;
    const profit = totalRevenue - totalCost;
    const growthFactor = 1 + durationInMonths * monthlyGrowthRate;

    return profit * growthFactor;
  }
}
