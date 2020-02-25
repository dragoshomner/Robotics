#ifndef APP_H
#define APP_H

void initializeRound() {
  adminAnswer = playerOneAnswer = playerTwoAnswer = 'Z';
  playerOneChose = playerTwoChose = false;
  livesChecked = false;
}

void resetRound() {
    initializeLEDs();
    initializeSevSegText();
    initializeRound();
}

void initializeGame() {
  playerOneLives = playerTwoLives = initialLives;
  resetRound();
}

void checkLives() {
  livesChecked = true;

  if (playerOneLives == 0 && playerTwoLives == 0) {
    strcpy(textPlayerOne, "  PU");
    strcpy(textPlayerTwo, "  PU"); 
    gameStarted = false;
  }
  else if (playerOneLives == 0 && playerTwoLives > 0) {
    strcpy(textPlayerOne, "ESOL");
    strcpy(textPlayerTwo, 
    "  azsfxdfcguhijokl;'\
    PU"); 
    gameStarted = false;
  }
  else if (playerOneLives > 0 && playerTwoLives == 0) {
    strcpy(textPlayerOne, "  PU");
    strcpy(textPlayerTwo, "ESOL"); 
    gameStarted = false;
  }
}

void getResults() {
  setSevSegText(textPlayerOne, playerOneAnswer);
  setSevSegText(textPlayerTwo, playerTwoAnswer);
  
  if (playerOneAnswer == adminAnswer) {
    lightLed(playerOneCorrectPin, playerOneWrongPin);
  }
  else {
    lightLed(playerOneWrongPin, playerOneCorrectPin);
    if (!livesChecked){
      playerOneLives --;
    }
  }
  
  if (playerTwoAnswer == adminAnswer) {
    lightLed(playerTwoCorrectPin, playerTwoWrongPin);
  }
  else {
    lightLed(playerTwoWrongPin, playerTwoCorrectPin);
    if (!livesChecked) {
      playerTwoLives --;
    }
  }

  checkLives();
}

void chooseAnswerPlayerOne() {
  if (playerOneButtonA.wasReleased()) {
    playerOneAnswer = 'A';
    playerOneChose = true;
  }
  else if (playerOneButtonB.wasReleased()) {
    playerOneAnswer = 'B';
    playerOneChose = true;
  }
  else if (playerOneButtonC.wasReleased()) {
    playerOneAnswer = 'C';
    playerOneChose = true;
  }
  else if (playerOneButtonD.wasReleased()) {
    playerOneAnswer = 'D';
    playerOneChose = true;
  }
}

void chooseAnswerPlayerTwo() {
  if (playerTwoButtonA.wasReleased()) {
    playerTwoAnswer = 'A';
    playerTwoChose = true;
  }
  else if (playerTwoButtonB.wasReleased()) {
    playerTwoAnswer = 'B';
    playerTwoChose = true;
  }
  else if (playerTwoButtonC.wasReleased()) {
    playerTwoAnswer = 'C';
    playerTwoChose = true;
  }
  else if (playerTwoButtonD.wasReleased()) {
    playerTwoAnswer = 'D';
    playerTwoChose = true;
  }
}

void chooseAnswerAdmin() {
  if (adminButtonA.wasReleased()) {
    adminAnswer = 'A';
  }
  else if (adminButtonB.wasReleased()) {
    adminAnswer = 'B';
  }
  else if (adminButtonC.wasReleased()) {
    adminAnswer = 'C';
  }
  else if (adminButtonD.wasReleased()) {
    adminAnswer = 'D';
  }
}

void updateApp() {
  if (!gameStarted) {
    if (startGameButton.wasReleased()) {
      gameStarted = true;
      initializeGame();
    }
  }
  else {
    if (adminAnswer == 'Z') {
      chooseAnswerAdmin();
    }
    else {
      if (!roundStarted) {
        if (startGameButton.wasReleased()) {
          roundStarted = true;
        }
      }
      else {
        if (!playerOneChose) {
          chooseAnswerPlayerOne();  
        }
        if (!playerTwoChose) {
          chooseAnswerPlayerTwo();
        }
        if (playerOneChose && playerTwoChose) {
          getResults();
          if (startGameButton.wasReleased()) {
            roundStarted = false;
            resetRound();
          }
        }
      }
    } 
  }
}
#endif
