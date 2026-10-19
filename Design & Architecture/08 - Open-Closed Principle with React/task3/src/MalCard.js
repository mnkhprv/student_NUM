import React, { Component } from "react";

class MalCard extends Component {
  render() {
    const { mal } = this.props;

    const cardStyle = {
      backgroundColor: mal.getColor(),
      border: "1px solid #333",
      borderRadius: "12px",
      padding: "16px",
      margin: "10px",
      width: "220px",
      textAlign: "center",
      boxShadow: "0 2px 6px rgba(0,0,0,0.2)",
      fontFamily: "sans-serif"
    };

    return (
      <div style={cardStyle}>
        <div style={{ fontSize: "40px" }}>{mal.getEmoji()}</div>
        <h2>{mal.name}</h2>
        <p><strong>Дуу:</strong> {mal.getSound()}</p>
      </div>
    );
  }
}

export default MalCard;