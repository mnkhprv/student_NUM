import React from "react";
import "./App.css";
import MalCard from "./MalCard";
import { Hourse, Camel, Cow, Sheep, Coat } from "./Mal";

function App() {
  const maluud = [
    new Hourse("Адуу"),
    new Camel("Тэмээ"),
    new Cow("Үхэр"),
    new Sheep("Хонь"),
    new Coat("Ямаа")
  ];

  const containerStyle = {
    display: "flex",
    flexWrap: "wrap",
    justifyContent: "center",
    padding: "20px"
  };

  return (
    <div className="App">
      <h1 style={{ textAlign: "center" }}>5 хошуу мал</h1>
      <div style={containerStyle}>
        {maluud.map((mal, index) => (
          <MalCard key={index} mal={mal} />
        ))}
      </div>
    </div>
  );
}

export default App;