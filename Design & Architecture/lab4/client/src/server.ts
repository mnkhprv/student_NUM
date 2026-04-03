import express from "express";
import cors from "cors";
import path from "path";
import { fileURLToPath } from "url";

const app = express();
const PORT = 3000;
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

app.use(cors());
app.use(express.json());
app.use(express.static(__dirname));

class TaxPayer {
  constructor(
    public totalIncome: number,
    public workedDays: number,
    public dailyIncome: number
  ) {}
}

interface TaxStrategy {
  calculate(taxPayer: TaxPayer): number;
}

class Tax2023Strategy implements TaxStrategy {
  calculate(taxPayer: TaxPayer): number {
    if (taxPayer.workedDays > 300) {
      return taxPayer.totalIncome * 0.15;
    } else {
      return taxPayer.totalIncome * 0.10;
    }
  }
}

class Tax2024Strategy implements TaxStrategy {
  calculate(taxPayer: TaxPayer): number {
    if (taxPayer.dailyIncome > 20000) {
      return taxPayer.dailyIncome * 0.10 * 365;
    } else {
      return taxPayer.dailyIncome * 0.05 * 365;
    }
  }
}

class TaxService {
  calculateTax(year: number, taxPayer: TaxPayer): number {
    let strategy: TaxStrategy;

    if (year === 2023) {
      strategy = new Tax2023Strategy();
    } else if (year === 2024) {
      strategy = new Tax2024Strategy();
    } else {
      throw new Error("Дэмжигдэхгүй он байна");
    }

    return strategy.calculate(taxPayer);
  }
}

const taxService = new TaxService();

app.get("/", (_request, response) => {
  response.sendFile(path.join(__dirname, "client.html"));
});

app.post("/tax/calculate", (request, response) => {
  try {
    const { year, totalIncome, workedDays, dailyIncome } = request.body;

    const taxPayer = new TaxPayer(totalIncome, workedDays, dailyIncome);
    const tax = taxService.calculateTax(year, taxPayer);

    response.json({
      success: true,
      year,
      tax
    });
  } catch {
    response.status(400).json({
      success: false,
      message: "Татвар бодоход алдаа гарлаа"
    });
  }
});

app.listen(PORT, () => {
  console.log(`Server ажиллаж байна: http://localhost:${PORT}`);
});
