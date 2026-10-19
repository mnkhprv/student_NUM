import { ProductService } from "@/services/ProductService"

const service = new ProductService();
const products = service.getAll();

export default function Products() {
  return (
    <div style={{ padding: 20 }}>
      <h1>Бүтээгдэхүүний жагсаалт</h1>
      <ul>
        {products.map((p) => (
          <li key={p.id}>
            {p.name} — ${p.price}
          </li>
        ))}
      </ul>
    </div>
  );
}