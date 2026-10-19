import { ProductService } from "../../services/ProductService";

const service = new ProductService();
const expensive = service.getExpensiveProducts();

export default function DetailPage() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Үнэтэй бүтээгдэхүүнүүд (1000$+)</h1>
      <ul>
        {expensive.map((p) => (
          <li key={p.id}>
            {p.name} — ${p.price}
          </li>
        ))}
      </ul>
    </div>
  );
}