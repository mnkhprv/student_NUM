const button = document.getElementById("calcBtn") as HTMLButtonElement;
const result = document.getElementById("result") as HTMLHeadingElement;

button.addEventListener("click", async () => {
  const year = Number((document.getElementById("year") as HTMLInputElement).value);
  const totalIncome = Number((document.getElementById("totalIncome") as HTMLInputElement).value);
  const workedDays = Number((document.getElementById("workedDays") as HTMLInputElement).value);
  const dailyIncome = Number((document.getElementById("dailyIncome") as HTMLInputElement).value);

  const response = await fetch("http://localhost:3000/tax/calculate", {
    method: "POST",
    headers: {
      "Content-Type": "application/json"
    },
    body: JSON.stringify({
      year,
      totalIncome,
      workedDays,
      dailyIncome
    })
  });

  const data = await response.json();

  if (data.success) {
    result.textContent = `${data.year} оны татвар: ${data.tax}₮`;
  } else {
    result.textContent = "Алдаа гарлаа";
  }
});
