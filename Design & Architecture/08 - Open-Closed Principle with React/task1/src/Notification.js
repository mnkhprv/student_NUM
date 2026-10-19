import React from "react";

const Notification = () => {
  const showNotification = () => {
    alert("Шинэ мэдэгдэл ирлээ!");
  };

  return (
    <div>
      <h2>Notification систем</h2>
      <button onClick={showNotification}>Мэдэгдэл харах</button>
    </div>
  );
};

export default Notification;