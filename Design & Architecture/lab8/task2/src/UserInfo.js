import React from "react";

const UserInfo = ({ ner, age, hobby }) => {
  return (
    <div style={{
      border: "1px solid #ccc",
      padding: "15px",
      borderRadius: "10px",
      margin: "10px",
      width: "300px"
    }}>
      <h2>Хэрэглэгчийн мэдээлэл</h2>
      <p><strong>Нэр:</strong> {ner}</p>
      <p><strong>Нас:</strong> {age}</p>
      <p><strong>Хобби:</strong> {hobby}</p>
    </div>
  );
};

export default UserInfo;