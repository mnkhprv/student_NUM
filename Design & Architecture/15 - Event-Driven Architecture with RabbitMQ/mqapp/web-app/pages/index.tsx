import { useState } from "react";

export default function Home() {
  const [message, setMessage] = useState("");
  const [status, setStatus] = useState("");

  const sendMessage = async () => {
    if (!message.trim()) return;
    const res = await fetch("/api/log", {
      method: "POST",
      body: JSON.stringify({ message }),
      headers: { "Content-Type": "application/json" },
    });
    const data = await res.json();
    setStatus(data.status);
    setMessage("");
  };

  return (
    <div style={{
      minHeight: "100vh",
      backgroundColor: "#1a1a1a",
      display: "flex",
      alignItems: "center",
      justifyContent: "center",
      fontFamily: "sans-serif",
    }}>
      <div style={{
        backgroundColor: "#222",
        border: "2px solid #FF6600",
        borderRadius: "12px",
        padding: "2.5rem",
        width: "100%",
        maxWidth: "480px",
        boxShadow: "0 0 24px rgba(255,102,0,0.3)",
      }}>
        {/* Logo + Title */}
        <div style={{ display: "flex", alignItems: "center", gap: "0.75rem", marginBottom: "1.5rem" }}>
          <div style={{
            width: 40, height: 40,
            backgroundColor: "#FF6600",
            borderRadius: "50%",
            display: "flex", alignItems: "center", justifyContent: "center",
            fontSize: "1.2rem",
          }}>
            🐇
          </div>
          <h1 style={{ color: "#FF6600", margin: 0, fontSize: "1.4rem", fontWeight: 700 }}>
            RabbitMQ Messenger
          </h1>
        </div>

        <p style={{ color: "#aaa", fontSize: "0.85rem", marginBottom: "1.5rem" }}>
          Queue: <span style={{ color: "#FF6600", fontWeight: 600 }}>logs</span>
        </p>

        {/* Input */}
        <div style={{ display: "flex", gap: "0.5rem" }}>
          <input
            value={message}
            onChange={(e) => setMessage(e.target.value)}
            onKeyDown={(e) => e.key === "Enter" && sendMessage()}
            placeholder="Лог мессеж бичнэ үү..."
            style={{
              flex: 1,
              padding: "0.6rem 0.9rem",
              fontSize: "0.95rem",
              backgroundColor: "#2e2e2e",
              border: "1px solid #FF6600",
              borderRadius: "8px",
              color: "#fff",
              outline: "none",
            }}
          />
          <button
            onClick={sendMessage}
            style={{
              padding: "0.6rem 1.1rem",
              backgroundColor: "#FF6600",
              color: "#fff",
              border: "none",
              borderRadius: "8px",
              fontWeight: 700,
              cursor: "pointer",
              fontSize: "0.95rem",
              transition: "background 0.2s",
            }}
            onMouseEnter={(e) => (e.currentTarget.style.backgroundColor = "#e05500")}
            onMouseLeave={(e) => (e.currentTarget.style.backgroundColor = "#FF6600")}
          >
            Send
          </button>
        </div>

        {/* Status */}
        {status && (
          <div style={{
            marginTop: "1rem",
            padding: "0.6rem 1rem",
            backgroundColor: "#2a1a00",
            border: "1px solid #FF6600",
            borderRadius: "8px",
            color: "#FF6600",
            fontSize: "0.85rem",
          }}>
            ✓ {status}
          </div>
        )}

        <p style={{ color: "#555", fontSize: "0.75rem", marginTop: "1.5rem", marginBottom: 0, textAlign: "center" }}>
          React → Producer → RabbitMQ → Consumer
        </p>
      </div>
    </div>
  );
}
