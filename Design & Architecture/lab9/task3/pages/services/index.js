import { useEffect, useState } from "react";

const styles = {
  page: {
    minHeight: "100vh",
    background: "#f5efe6",
    padding: "3rem 1.5rem",
  },
  inner: {
    maxWidth: "620px",
    margin: "0 auto",
  },
  header: {
    display: "flex",
    alignItems: "center",
    justifyContent: "space-between",
    marginBottom: "2rem",
  },
  title: {
    fontSize: "1.75rem",
    fontWeight: 700,
    color: "#3b2f2f",
  },
  addBtn: {
    background: "#7c4f2f",
    color: "#fff8f0",
    padding: "0.55rem 1.4rem",
    borderRadius: "10px",
    fontWeight: 600,
    fontSize: "0.9rem",
    textDecoration: "none",
    boxShadow: "0 3px 10px rgba(124,79,47,0.2)",
  },
  empty: {
    color: "#a08060",
    textAlign: "center",
    marginTop: "3rem",
    fontSize: "0.97rem",
  },
  card: {
    background: "#fff8f0",
    border: "1px solid #e8d5b7",
    borderRadius: "14px",
    padding: "1.25rem 1.5rem",
    marginBottom: "1rem",
    boxShadow: "0 3px 14px rgba(100,60,20,0.08)",
  },
  cardTitle: {
    fontWeight: 700,
    fontSize: "1.08rem",
    color: "#3b2f2f",
    marginBottom: "0.35rem",
  },
  cardDesc: {
    color: "#7a6050",
    fontSize: "0.93rem",
    lineHeight: 1.6,
  },
  backLink: {
    display: "inline-block",
    marginTop: "2rem",
    color: "#7c4f2f",
    fontSize: "0.9rem",
  },
};

export default function Services() {
  const [services, setServices] = useState([]);

  useEffect(() => {
    fetch("/api/services")
      .then((res) => res.json())
      .then(setServices);
  }, []);

  return (
    <div style={styles.page}>
      <div style={styles.inner}>
        <div style={styles.header}>
          <h1 style={styles.title}>Үйлчилгээний жагсаалт</h1>
          <a href="/services/add" style={styles.addBtn}>+ Нэмэх</a>
        </div>

        {services.length === 0 ? (
          <p style={styles.empty}>Одоогоор үйлчилгээ байхгүй байна.</p>
        ) : (
          services.map((s) => (
            <div key={s._id} style={styles.card}>
              <div style={styles.cardTitle}>{s.title}</div>
              <div style={styles.cardDesc}>{s.description}</div>
            </div>
          ))
        )}

        <a href="/" style={styles.backLink}>← Нүүр хуудас</a>
      </div>
    </div>
  );
}