const message: string = "Сайн байна уу, Webpack бүхий TypeScript! минь";
console.log(message);

const par = document.getElementsByClassName("paragraph")[0];

const span = document.createElement("span");
span.textContent = "Энэ техт динамикаар нэмэгдэж байна.";
par?.appendChild(span);

const button = document.getElementById("changeBtn");
const div = document.getElementById("div");

button?.addEventListener("click", () => {
  if (div) {
    div.textContent = "uurchlugdsun";
  }
});

const messageForm = document.getElementById("messageForm") as HTMLFormElement | null;
const messageInput = document.getElementById("messageInput") as HTMLInputElement | null;

messageForm?.addEventListener("submit", (event) => {
  event.preventDefault();

  if (messageInput) {
    console.log(messageInput.value);
  }
});
