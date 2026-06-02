// pages/users.tsx
import { useEffect, useState } from 'react';
import Link from 'next/link';

interface User {
    id: number;
    name: string;
    email: string;
}

export default function UsersPage() {
    const [users, setUsers] = useState<User[]>([]);

    useEffect(() => {
        fetch('/api/users')
            .then((res) => res.json())
            .then((data) => setUsers(data));
    }, []);

    return (
        <div style={styles.page}>
            <div style={styles.container}>
                <Link href="/" style={styles.back}>← Нүүр хуудас</Link>
                <h1 style={styles.title}>Хэрэглэгчид</h1>
                <div style={styles.divider} />
                <ul style={styles.list}>
                    {users.map((user) => (
                        <li key={user.id} style={styles.card}>
                            <span style={styles.name}>{user.name}</span>
                            <span style={styles.detail}>{user.email}</span>
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
