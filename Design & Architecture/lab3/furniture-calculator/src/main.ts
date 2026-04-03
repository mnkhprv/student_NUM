import { CutOptimizer } from "./business/CutOptimizer";
import { CostCalculator } from "./business/CostCalculator";
import { ProfitEstimator } from "./business/ProfitEstimator";
import { Chair, Table } from "./domain/Furniture";
import { Material } from "./domain/Material";

// Материал үүсгэх
const wood = new Material("Мод", 5000, 200, 100); // Материалын нэр, үнэ, өргөн, өндөр

// Сандал болон ширээ үүсгэх
const chair1 = new Chair("Сандал", wood, 40, 40);
const chair2 = new Chair("Сандал", wood, 45, 45);
const table1 = new Table("Ширээ", wood, 120, 60);

// Материалын зүсэлтийг оновчлох
const isOptimized = CutOptimizer.optimizeCutting(wood, [
 { width: chair1.requiredWidth, height: chair1.requiredHeight },
 { width: chair2.requiredWidth, height: chair2.requiredHeight },
 { width: table1.requiredWidth, height: table1.requiredHeight },
]);
console.log(`Материал оновчтой зүсэгдсэн үү? ${isOptimized ? "Тийм" : "Үгүй"}`);

// Зардлын тооцоолол
const totalCost = CostCalculator.calculateTotalCost([chair1, chair2, table1]);
console.log(`Нийт зардал: ${totalCost}₮`);

// Ашгийн тооцоо (1 сарын дараах)
const estimatedProfit = ProfitEstimator.estimateProfit([chair1, chair2, table1], 15000, 1);
console.log(`1 сарын дараах борлуулалтын ашиг: ${estimatedProfit.toFixed(2)}₮`);
