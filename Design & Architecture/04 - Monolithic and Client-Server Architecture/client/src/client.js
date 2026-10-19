const button = document.getElementById("calcBtn");
const result = document.getElementById("result");

button.addEventListener("click", async () => {
  const year = Number(document.getElementById("year").value);
  const totalIncome = Number(document.getElementById("totalIncome").value);
  const workedDays = Number(document.getElementById("workedDays").value);
  const dailyIncome = Number(document.getElementById("dailyIncome").value);

  const response = await fetch("/tax/calculate", {
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
  result.textContent = data.success
    ? `${data.year} оны татвар: ${data.tax}₮`
    : "Алдаа гарлаа";
});
