const hangmanImage = document.querySelector(".hangman-box img");
const wordDisplay = document.querySelector(".word-display");
const guessessText = document.querySelector(".guesses-text b");
const keyboardDiv = document.querySelector(".keyboard");
const gameModal = document.querySelector(".game-modal");
const playAgainBtn = document.querySelector(".play-again");

let currentWord, correctLetters = [], wrongGuessCount = 0;
const maxGuesses = 6;

const resetGame = () => {
  correctLetters = [];
  wrongGuessCount = 0;
  guessessText.innerText = `${wrongGuessCount} / ${maxGuesses}`;
  hangmanImage.src = `images/hangman-${wrongGuessCount}.svg`;
  keyboardDiv.querySelectorAll("button").forEach(btn => btn.disabled = false);
  wordDisplay.innerHTML = currentWord.split("").map(() => `<li class="letter"></li>`).join("");
  gameModal.classList.remove("show");

}

const getRandomWord = () => {
  const { word, hint } = wordList[Math.floor(Math.random() * wordList.length)];
  currentWord = word.toLocaleLowerCase();
  console.log(word);
  document.querySelector(".hint-text b")
  .innerText = hint;
  resetGame();
}
const gameOver = (isVictory) => {
  setTimeout(() => {
    const modalText = isVictory ? `You found the word` : `The correct word was`;
    gameModal.querySelector("img").src = `images/${isVictory ? `victory` : `lost`}.gif`;
    gameModal.querySelector("h4").innerText = `${isVictory ? `Congrats!` : `GameOver`}`;
    gameModal.querySelector("p").innerHTML = `${modalText} <b>${currentWord}</b>`;
    gameModal.classList.add("show");
  }, 300)
}

const initGame = (button, clickedLetter) => {
  if(currentWord.includes(clickedLetter)) {
    [...currentWord].forEach((letter, index) => {
      if (letter === clickedLetter){
        correctLetters.push(letter);
        wordDisplay.querySelectorAll("li")[index].innerText = letter;
        wordDisplay.querySelectorAll("li")[index].classList.add("guessed");
      }
    })
  } else {
    wrongGuessCount++;
    hangmanImage.src = `images/hangman-${wrongGuessCount}.svg`;
  }
  button.disabled = true;
  guessessText.innerText = `${wrongGuessCount} / ${maxGuesses}`;

  const allLettersGuessed = [...currentWord].every(letter => correctLetters.includes(letter));
  if (wrongGuessCount === maxGuesses) return gameOver(false);
  if (allLettersGuessed) return gameOver(true);
}


for (let i = 97; i <= 122; i++) {
  const button = document.createElement("button");
  const letter = String.fromCharCode(i);
  button.innerText = letter;
  button.classList.add("key");
  button.dataset.letter = letter;
  keyboardDiv.appendChild(button);
  button.addEventListener("click", e => initGame(e.target, letter));
}

document.addEventListener("keydown", e => {
  if (e.key.match(/^[a-z]$/i)) {
      const letter = e.key.toLowerCase();
      const button = keyboardDiv.querySelector(`button[data-letter="${letter}"]:not(:disabled)`);
      if (button) initGame(button, letter);
  }
});

getRandomWord();
playAgainBtn.addEventListener("click", getRandomWord);