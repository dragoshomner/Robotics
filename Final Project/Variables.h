#ifndef VARIABLES_H
#define VARIABLES_H

const char* 
  defaultText = "0C8A";
char 
  textPlayerOne[5], 
  textPlayerTwo[5];
char 
  adminAnswer = 'Z',
  playerOneAnswer = 'Z',
  playerTwoAnswer = 'Z';
bool 
  gameStarted = false,
  playerOneChose = false,
  playerTwoChose = false, 
  roundStarted = false,
  livesChecked = false;
const int 
  initialLives = 3;
int
  playerOneLives = initialLives,
  playerTwoLives = initialLives;

#endif
