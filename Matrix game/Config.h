#ifndef CONFIG_H
#define CONFIG_H

struct configuration{
  int difficulty = 2;
  int numberOfPlayers = 1;
  int currentPlayer = 1;
  bool sensorCalibrating = false;
  bool gameStarted = false;
  bool gameCounterFinished = false;
  bool gamePlayerIsInside = false;
  bool gamePlaying = false;
  int startingLevel = 1;
  int gamesPerLevel = 5;
  int bonusTimePerCompletedLevel = 3;
  int defaultTime = 10;
  int remainingTime;
  int scores[maximumNumberOfPlayers + 1];
  int leaderBoard[maximumNumberOfPlayers];
  bool gameFinished = false;
  bool gameNextPlayer = false;
  int gameWinner = 1;
  bool newHighscore = false;
  int highscore[4];
  
  bool sensorUpDownCalibrated = false, sensorLeftRightCalibrated = false;
}Config;

#endif
