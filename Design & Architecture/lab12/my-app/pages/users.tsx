// pages/users.tsx
import Link from 'next/link';
import { gql } from '@apollo/client';
import { useQuery } from '@apollo/client/react';

interface User {
    id: string;
    name: string;
    email: string;
}

interface GetUsersData {
    getUsers: User[];
}

const GET_USERS = gql`
    query GetUsers {
        getUsers {
            id
            name
            email
        }
    }
`;

export default function UsersPage() {
    const { loading, error, data } = useQuery<GetUsersData>(GET_USERS);

    return (
        <div style={styles.page}>
            <div style={styles.container}>
                <Link href="/" style={styles.back}>← Нүүр хуудас</Link>
                <h1 style={styles.title}>Хэрэглэгчид</h1>
                <div style={styles.divider} />

                {loading && <p style={styles.status}>Унших...</p>}
                {error && <p style={styles.error}>Алдаа гарлаа: {error.message}</p>}

                <ul style={styles.list}>
                    {data?.getUsers.map((user) => (
                        <li key={user.id} style={styles.card}>
                            <span style={styles.name}>{user.name}</span>
                            <span style={styles.email}>{user.email}</span>
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
    back: {
        display: 'inline-block',
        color: 'var(--muted)',
        fontSize: '0.85rem',
        textDecoration: 'none',
        marginBottom: '1rem',
    },
    title: {
        fontSize: '1.8rem',
        color: 'var(--orange-light)',
        letterSpacing: '0.05em',
        marginBottom: '0.5rem',
    },
    divider: {
        height: '2px',
        background: 'linear-gradient(to right, var(--orange), transparent)',
        marginBottom: '1.5rem',
        borderRadius: '2px',
    },
    status: {
        color: 'var(--muted)',
        fontStyle: 'italic',
    },
    error: {
        color: '#e85555',
        fontSize: '0.9rem',
    },
    list: {
        listStyle: 'none',
        display: 'flex',
        flexDirection: 'column',
        gap: '0.75rem',
    },
    card: {
        background: 'var(--card)',
        border: '1px solid var(--border)',
        borderRadius: '10px',
        padding: '0.85rem 1.2rem',
        display: 'flex',
        flexDirection: 'column',
        gap: '0.2rem',
    },
    name: {
        color: 'var(--text)',
        fontWeight: 'bold',
        fontSize: '1rem',
    },
    email: {
        color: 'var(--muted)',
        fontSize: '0.85rem',
    },
};
