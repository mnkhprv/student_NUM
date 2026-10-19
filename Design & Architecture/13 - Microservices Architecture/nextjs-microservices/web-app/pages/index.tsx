import { useEffect, useState } from "react";

export default function Home() {
  const [users, setUsers] = useState<{ name: string }[]>([]);
  const [products, setProducts] = useState<{ name: string }[]>([]);

  useEffect(() => {
    Promise.all([
      fetch("/api/users").then(r => r.json()).catch(() => []),
      fetch("/api/products").then(r => r.json()).catch(() => []),
    ]).then(([u, p]) => {
      setUsers(u);
      setProducts(p);
    });
  }, []);

  return (
    <div>
      <h1>Microservices App</h1>

      <h2>Users</h2>
      <ul>
        {users.map((u, i) => <li key={i}>{u.name}</li>)}
      </ul>

      <h2>Products</h2>
      <ul>
        {products.map((p, i) => <li key={i}>{p.name}</li>)}
      </ul>
    </div>
  );
}
