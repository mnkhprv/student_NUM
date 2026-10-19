import { Material } from "../domain/Material";
import { Furniture } from "../domain/Furniture";

export class CutOptimizer {
  static calculateRemainingMaterial(
    material: Material,
    furnitureList: Furniture[]
  ): number {
    let totalUsedArea = 0;

    furnitureList.forEach((furniture) => {
      totalUsedArea += furniture.calculateMaterialUsage();
    });

    return material.getRemainingArea(totalUsedArea);
  }

  static optimizeCutting(
    material: Material,
    items: { width: number; height: number }[]
  ): boolean {
    let totalUsedArea = 0;

    items.forEach((item) => {
      totalUsedArea += item.width * item.height;
    });

    return totalUsedArea <= material.getTotalArea();
  }
}
