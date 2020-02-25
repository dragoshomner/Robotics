#ifndef BUTTONS_H
#define BUTTONS_H

Button 
  playerOneButtonA(playerOneButtonAPin),
  playerOneButtonB(playerOneButtonBPin),
  playerOneButtonC(playerOneButtonCPin),
  playerOneButtonD(playerOneButtonDPin),
  playerTwoButtonA(playerTwoButtonAPin),
  playerTwoButtonB(playerTwoButtonBPin),
  playerTwoButtonC(playerTwoButtonCPin),
  playerTwoButtonD(playerTwoButtonDPin),
  adminButtonA(adminButtonAPin),
  adminButtonB(adminButtonBPin),
  adminButtonC(adminButtonCPin),
  adminButtonD(adminButtonDPin);

Button startGameButton(startGamePin);

void initializeButtonsPins() {
  // player 1 buttons ABCD
  pinMode(playerOneButtonAPin, INPUT_PULLUP);
  pinMode(playerOneButtonBPin, INPUT_PULLUP);
  pinMode(playerOneButtonCPin, INPUT_PULLUP);
  pinMode(playerOneButtonDPin, INPUT_PULLUP);

  // player 2 buttons ABCD
  pinMode(playerTwoButtonAPin, INPUT_PULLUP);
  pinMode(playerTwoButtonBPin, INPUT_PULLUP);
  pinMode(playerTwoButtonCPin, INPUT_PULLUP);
  pinMode(playerTwoButtonDPin, INPUT_PULLUP);

  // admin buttons ABCD
  pinMode(adminButtonAPin, INPUT_PULLUP);
  pinMode(adminButtonBPin, INPUT_PULLUP);
  pinMode(adminButtonCPin, INPUT_PULLUP);
  pinMode(adminButtonDPin, INPUT_PULLUP);

  // player 1
  playerOneButtonA.begin();
  playerOneButtonB.begin();
  playerOneButtonC.begin();
  playerOneButtonD.begin();

  // player 2
  playerTwoButtonA.begin();
  playerTwoButtonB.begin();
  playerTwoButtonC.begin();
  playerTwoButtonD.begin();

  // admin
  adminButtonA.begin();
  adminButtonB.begin();
  adminButtonC.begin();
  adminButtonD.begin();

  startGameButton.begin();
}

void readButtons() {
  // player 1
  playerOneButtonA.read();
  playerOneButtonB.read();
  playerOneButtonC.read();
  playerOneButtonD.read();

  // player 2
  playerTwoButtonA.read();
  playerTwoButtonB.read();
  playerTwoButtonC.read();
  playerTwoButtonD.read();

  //admin
  adminButtonA.read();
  adminButtonB.read();
  adminButtonC.read();
  adminButtonD.read();

  startGameButton.read();
}

#endif
