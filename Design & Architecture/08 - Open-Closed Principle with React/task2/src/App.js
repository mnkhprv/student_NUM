import React from "react";
import "./App.css";
import UserInfo from "./UserInfo";
import Notification from "./Notification";

function App() {
  return (
    <div className="App">
      <h1>React System Example</h1>

      <UserInfo ner="Munkhpurev" age="21" hobby="Chess" />

      <Notification />
    </div>
  );
}

export default App;