// pages/products.tsx
import { useEffect, useState } from 'react';
import Link from 'next/link';

interface Product {
    id: number;
    name: string;
    price: number;
}

export default function ProductsPage() {
    const [products, setProducts] = useState<Product[]>([]);

    useEffect(() => {
        fetch('/api/products')
            .then((res) => res.json())
            .then((data) => setProducts(data));
    }, []);

    return (
        <div style={styles.page}>
            <div style={styles.container}>
                <Link href="/" style={styles.back}>← Нүүр хуудас</Link>
                <h1 style={styles.title}>Бараанууд</h1>
                <div style={styles.divider} />
                <ul style={styles.list}>
                    {products.map((product) => (
                        <li key={product.id} style={styles.card}>
                            <span style={styles.name}>{product.name}</span>
                            <span style={styles.detail}>{product.price.toLocaleString()}₮</span>
                        </li>
                    ))}
                </ul>
            </div>
        </div>
    );
}

const styles: Record<string, React.CSSProperties> = {
    page: {
        minHeight: '100vh',
        background: 'var(--bg)',
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        padding: '2rem',
    },
    container: {
        background: 'var(--surface)',
        border: '1px solid var(--border)',
        borderRadius: '16px',
        padding: '2.5rem',
        width: '100%',
        maxWidth: '520px',
        boxShadow: '0 8px 32px rgba(0,0,0,0.5)',
    },
    back: {
        display: 'inline-block',
        color: 'var(--muted)',
        fontSize: '0.85rem',
        textDecoration: 'none',
        marginBottom: '1rem',
    },
    title: {
        fontSize: '1.6rem',
        color: 'var(--orange-light)',
        letterSpacing: '0.04em',
        marginBottom: '0.5rem',
    },
    divider: {
        height: '2px',
        background: 'linear-gradient(to right, var(--orange), transparent)',
        margin: '1rem 0 1.25rem',
        borderRadius: '2px',
    },
    list: {
        listStyle: 'none',
        display: 'flex',
        flexDirection: 'column',
        gap: '0.6rem',
    },
    card: {
        background: 'var(--card)',
        border: '1px solid var(--border)',
        borderRadius: '10px',
        padding: '0.75rem 1.1rem',
        display: 'flex',
        justifyContent: 'space-between',
        alignItems: 'center',
    },
    name: {
        color: 'var(--text)',
        fontWeight: 'bold',
        fontSize: '0.95rem',
    },
    detail: {
        color: 'var(--muted)',
        fontSize: '0.85rem',
    },
};
