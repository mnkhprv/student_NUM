// pages/index.tsx
import Link from 'next/link';

const pages = [
    { href: '/users', label: 'Хэрэглэгчид', desc: 'Бүртгэлтэй хэрэглэгчдийн жагсаалт' },
    { href: '/products', label: 'Бараанууд', desc: 'Барааны жагсаалт болон үнэ' },
];

export default function Home() {
    return (
        <div style={styles.page}>
            <div style={styles.container}>
                <h1 style={styles.title}>Express.js + Next.js</h1>
                <p style={styles.subtitle}>Хуудас сонгоно уу</p>
                <div style={styles.divider} />
                <ul style={styles.list}>
                    {pages.map((p) => (
                        <li key={p.href}>
                            <Link href={p.href} style={styles.card}>
                                <span style={styles.label}>{p.label}</span>
                                <span style={styles.desc}>{p.desc}</span>
                            </Link>
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
        maxWidth: '480px',
        boxShadow: '0 8px 32px rgba(0,0,0,0.5)',
    },
    title: {
        fontSize: '1.6rem',
        color: 'var(--orange-light)',
        letterSpacing: '0.04em',
        marginBottom: '0.3rem',
    },
    subtitle: {
        color: 'var(--muted)',
        fontSize: '0.95rem',
        marginBottom: '0.5rem',
    },
    divider: {
        height: '2px',
        background: 'linear-gradient(to right, var(--orange), transparent)',
        margin: '1.25rem 0',
        borderRadius: '2px',
    },
    list: {
        listStyle: 'none',
        display: 'flex',
        flexDirection: 'column',
        gap: '0.75rem',
    },
    card: {
        display: 'flex',
        flexDirection: 'column',
        gap: '0.25rem',
        background: 'var(--card)',
        border: '1px solid var(--border)',
        borderRadius: '10px',
        padding: '1rem 1.2rem',
        textDecoration: 'none',
        transition: 'border-color 0.2s',
    },
    label: {
        color: 'var(--orange-light)',
        fontWeight: 'bold',
        fontSize: '1rem',
    },
    desc: {
        color: 'var(--muted)',
        fontSize: '0.85rem',
    },
};
