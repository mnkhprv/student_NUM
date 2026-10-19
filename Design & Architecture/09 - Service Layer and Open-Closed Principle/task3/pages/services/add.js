import { useState } from "react";
import { useRouter } from "next/router";

const styles = {
  page: {
    minHeight: "100vh",
    background: "#f5efe6",
    display: "flex",
    alignItems: "center",
    justifyContent: "center",
    padding: "2rem 1.5rem",
  },
  card: {
    background: "#fff8f0",
    border: "1px solid #e8d5b7",
    borderRadius: "16px",
    padding: "2.5rem 3rem",
    width: "100%",
    maxWidth: "460px",
    boxShadow: "0 6px 28px rgba(100,60,20,0.11)",
  },
  title: {
    fontSize: "1.6rem",
    fontWeight: 700,
    color: "#3b2f2f",
    marginBottom: "1.75rem",
  },
  label: {
    display: "block",
    fontSize: "0.85rem",
    fontWeight: 600,
    color: "#7a6050",
    marginBottom: "0.4rem",
    letterSpacing: "0.04em",
    textTransform: "uppercase",
  },
  input: {
    width: "100%",
    border: "1.5px solid #d6bfa0",
    borderRadius: "10px",
    padding: "0.7rem 1rem",
    fontSize: "0.97rem",
    background: "#fffbf5",
    color: "#3b2f2f",
    outline: "none",
    marginBottom: "1.25rem",
    fontFamily: "inherit",
  },
  textarea: {
    width: "100%",
    border: "1.5px solid #d6bfa0",
    borderRadius: "10px",
    padding: "0.7rem 1rem",
    fontSize: "0.97rem",
    background: "#fffbf5",
    color: "#3b2f2f",
    outline: "none",
    height: "120px",
    resize: "vertical",
    marginBottom: "1.5rem",
    fontFamily: "inherit",
  },
  btn: {
    width: "100%",
    background: "#7c4f2f",
    color: "#fff8f0",
    border: "none",
    borderRadius: "10px",
    padding: "0.8rem",
    fontSize: "1rem",
    fontWeight: 700,
    cursor: "pointer",
    boxShadow: "0 3px 12px rgba(124,79,47,0.22)",
    fontFamily: "inherit",
  },
  backLink: {
    display: "inline-block",
    marginTop: "1.1rem",
    color: "#7c4f2f",
    fontSize: "0.88rem",
  },
};

export default function AddService() {
  const [title, setTitle] = useState("");
  const [description, setDescription] = useState("");
  const router = useRouter();

  const handleSubmit = async (e) => {
    e.preventDefault();
    await fetch("/api/services", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ title, description }),
    });
    router.push("/services");
  };

  return (
    <div style={styles.page}>
      <div style={styles.card}>
        <h1 style={styles.title}>Үйлчилгээ нэмэх</h1>
        <form onSubmit={handleSubmit}>
          <label style={styles.label}>Гарчиг</label>
          <input
            type="text"
            placeholder="Үйлчилгээний нэр"
            style={styles.input}
            value={title}
            onChange={(e) => setTitle(e.target.value)}
          />
          <label style={styles.label}>Тайлбар</label>
          <textarea
            placeholder="Дэлгэрэнгүй тайлбар..."
            style={styles.textarea}
            value={description}
            onChange={(e) => setDescription(e.target.value)}
          />
          <button type="submit" style={styles.btn}>Хадгалах</button>
        </form>
        <a href="/services" style={styles.backLink}>← Буцах</a>
      </div>
    </div>
  );
}