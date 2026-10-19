const styles = {
  page: {
    minHeight: "100vh",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    background: "#f5efe6",
    padding: "2rem",
  },
  card: {
    background: "#fff8f0",
    borderRadius: "16px",
    boxShadow: "0 6px 32px rgba(100,60,20,0.12)",
    padding: "3rem 3.5rem",
    maxWidth: "480px",
    width: "100%",
    textAlign: "center",
    border: "1px solid #e8d5b7",
  },
  badge: {
    display: "inline-block",
    background: "#d4a96a",
    color: "#fff",
    borderRadius: "999px",
    padding: "4px 16px",
    fontSize: "0.78rem",
    fontWeight: 700,
    letterSpacing: "0.08em",
    marginBottom: "1.2rem",
    textTransform: "uppercase",
  },
  title: {
    fontSize: "2rem",
    fontWeight: 700,
    color: "#3b2f2f",
    marginBottom: "0.75rem",
  },
  sub: {
    color: "#7a6050",
    fontSize: "0.97rem",
    lineHeight: 1.65,
    marginBottom: "2rem",
  },
  link: {
    display: "inline-block",
    background: "#7c4f2f",
    color: "#fff8f0",
    padding: "0.7rem 2rem",
    borderRadius: "10px",
    fontWeight: 600,
    fontSize: "0.97rem",
    boxShadow: "0 3px 10px rgba(124,79,47,0.22)",
    transition: "background 0.2s",
    textDecoration: "none",
  },
};

export default function Home() {
  return (
    <div style={styles.page}>
      <div style={styles.card}>
        <span style={styles.badge}>Lab 9 · Task 3</span>
        <h1 style={styles.title}>Эхлэл хуудас</h1>
        <p style={styles.sub}>
          Service давхарга · Open/Closed Principle · MongoDB
        </p>
        <a href="/services" style={styles.link}>
          Үйлчилгээний жагсаалт руу →
        </a>
      </div>
    </div>
  );
}