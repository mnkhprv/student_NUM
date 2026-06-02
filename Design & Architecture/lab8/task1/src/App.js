import React from "react";
import "./App.css";
import UserInfo from "./UserInfo";
import Button from "./Button";

function App() {
  const style1 = {
    backgroundColor: "blue", 
    color: "white",
    padding: "5px", 
    border: "1px solid #000",
    borderRadius: "5px",
    width: "100px",
    height: "auto"
  };

  const action1 = () => {
    alert("you are screwed");
  };

  return (
    <div className="App">
      <UserInfo ner="Munkhpurev" age="21" hobby="Chess"/>
      <Button action={action1} style={style1} label={"Play then read"}/>
    </div>
  );
}

export default App;