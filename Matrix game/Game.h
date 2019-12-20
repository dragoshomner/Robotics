#ifndef GAME_H
#define GAME_H

#include "Sensor.h"
#include "Matrix.h"

class Game{
  private:
    Sensor sensorUpDown, sensorLeftRight;
    Matrix matrix;
    
    bool playerTurn = false;
    int currentLevel;
    int currentPlayer = 1;
    bool playerIsCenter = true;
    int isUpCounter = 0, isDownCounter = 0, isLeftCounter = 0, isRightCounter = 0, isCenterCounter = 0;
    const int validationCounter = 10;
    int lastDistancesUpDown[5], lastDistancesLeftRight[5], indexLastDistances;
    byte moves[maximumNumberOfMoves];
    byte totalMoves, currentMove;
    unsigned long lastTimeClock;

    void checkPlayerIsInside();
    bool areStabilizedDistances(int, int);
    void checkPosition(int);
    void restart();
    void resetGame();
    void getLeaderBoard();
    
  public:
    void initialize();
    void update();
    int getLeftRightDistance();
    void calibrateSensors();
    void getWinner();
};

// initialize all the parameters and object used in the game, such as sensors or matrix

void Game::initialize()
{
  sensorUpDown.initialize(SENSOR_UP_DOWN_PINS.echo, SENSOR_UP_DOWN_PINS.trig);
  sensorLeftRight.initialize(SENSOR_LEFT_RIGHT_PINS.echo, SENSOR_LEFT_RIGHT_PINS.trig);
  matrix.initialize();
  randomSeed(analogRead(0));
  Config.currentPlayer = 1;
  for(int i = 0 ; i < 10 ; i++){
    Config.scores[i] = 0;
  }
}

void Game::calibrateSensors()
{
  if(sensorUpDown.isCalibrated()){
    Config.sensorUpDownCalibrated = true;
  }
  if(sensorLeftRight.isCalibrated()){
    Config.sensorLeftRightCalibrated = true;
  }
}

void Game::update()
{
  // check if both sensors hits the wall, in the calibrating screen
  if(!Config.sensorUpDownCalibrated || !Config.sensorLeftRightCalibrated){
    calibrateSensors();
  }

  // check if the player is in the middle of the game zone, in the "go inside" screen
  else if(!Config.gamePlayerIsInside){
    checkPlayerIsInside();
  }

  else if(!Config.gameCounterFinished){
    // At this point, the sensors are calibrated and the game start counting down
 
    matrix.initialize();
    matrix.showCounter();
    Config.gameCounterFinished = true;
    Config.gamePlaying = true;
    playerTurn = false;
    currentLevel = (Config.startingLevel - 1) * Config.gamesPerLevel;
    
    Config.remainingTime = Config.defaultTime;
  }

  else if(Config.gamePlaying){
    // At this point the game started

    if(!playerTurn){
      totalMoves = min((currentLevel - 1) / Config.gamesPerLevel + 1, maximumNumberOfMoves - 1);
      for(int movement = 0 ; movement < totalMoves ; movement ++){
        int moveDirection = random(1, 5);
        matrix.showDirection(moveDirection);

        // the delay is used because is better than checking the difference of the times, because I want to freeze the system while the 
        // matrix show the moves and, moreover, it is a loading screen
        
        moves[movement] = moveDirection;
        delay(1000);
        matrix.showDot();
        delay(1000);
      }

      // blinks the screen to let user know that the sequence of movements is finished and will start his turn
      matrix.showBlank();
      delay(500);
      matrix.showDot();

      lastTimeClock = millis();
      
      playerTurn = true;
      currentMove = 0;
    }
    else if(playerTurn){
      
      // counter down
      if((unsigned long)millis() - lastTimeClock >= SECOND){
        lastTimeClock = millis();
        Config.remainingTime --;
        if(Config.remainingTime <= 0){
          Config.currentPlayer ++;
          matrix.showFinished();
          restart();
          if(Config.currentPlayer <= Config.numberOfPlayers){
            Config.gameNextPlayer = true;
            Config.sensorUpDownCalibrated = false;
            Config.sensorLeftRightCalibrated = false;
          }
          else{
            getWinner();
            getLeaderBoard();
            resetGame();
          }
        }
      }

      // algorithm of stabilization the sensors for a more precise human position detection
      
      int distanceUpDown = sensorUpDown.getDistance();
      int distanceLeftRight = sensorLeftRight.getDistance();
    
      if(playerIsCenter){
        bool isUp = sensorUpDown.isClose(distanceUpDown) && sensorLeftRight.isWall(distanceLeftRight);
        bool isDown = sensorUpDown.isFar(distanceUpDown) && sensorLeftRight.isWall(distanceLeftRight);
        bool isLeft = sensorUpDown.isWall(distanceUpDown) && sensorLeftRight.isClose(distanceLeftRight);
        bool isRight = sensorUpDown.isWall(distanceUpDown) && sensorLeftRight.isFar(distanceLeftRight);

        isUpCounter = isUp ? isUpCounter + 1 : isUpCounter;
        isDownCounter = isDown ? isDownCounter + 1 : isDownCounter;
        isLeftCounter = isLeft ? isLeftCounter + 1 : isLeftCounter;
        isRightCounter = isRight ? isRightCounter + 1 : isRightCounter;

        // use the delay to freeze the system while loading the current position of the player
        // moreover, is a good practice for stabilising the sensors

        if(isUpCounter > validationCounter){
          matrix.showDirection(UP); 
          delay(250);
          playerIsCenter = false;
          checkPosition(UP);
        }
        else if(isDownCounter > validationCounter){
          matrix.showDirection(DOWN); 
          delay(250);
          playerIsCenter = false;
          checkPosition(DOWN);
        }
        else if(isLeftCounter > validationCounter){
          matrix.showDirection(LEFT); 
          delay(250);
          playerIsCenter = false;
          checkPosition(LEFT);
        }
        else if(isRightCounter > validationCounter){
          matrix.showDirection(RIGHT); 
          delay(250);
          playerIsCenter = false;
          checkPosition(RIGHT);
        }
      }
      
      else{ 
        bool isCenter = sensorUpDown.isCenter(distanceUpDown) && sensorLeftRight.isCenter(distanceLeftRight); 
        isCenterCounter = isCenter ? isCenterCounter + 1 : isCenterCounter;
        
        if(isCenterCounter > validationCounter){
          matrix.showDot(); 
          delay(250);
          playerIsCenter = true; 
          if(currentMove >= totalMoves){
            playerTurn = false;
            currentLevel ++;
            Config.scores[Config.currentPlayer] += 1;
            Config.remainingTime += Config.bonusTimePerCompletedLevel * (currentLevel / Config.gamesPerLevel + 1); 

            if(Config.scores[Config.currentPlayer] > Config.highscore[Config.difficulty]){
              Config.highscore[Config.difficulty] = Config.scores[Config.currentPlayer];
              Config.newHighscore = true;
              EEPROM.write(Config.difficulty - 1, Config.highscore[Config.difficulty]);
            }

            // a breathing second for the player -> freeze the system
            delay(1000);
          }
          isCenterCounter = isUpCounter = isLeftCounter = isRightCounter = isDownCounter = 0;
        }
      }
    }
  }
}

int Game::getLeftRightDistance()
{
  return sensorLeftRight.getDistance();
}

void Game::checkPlayerIsInside()
{
  int distanceUpDown = sensorUpDown.getDistance();
  int distanceLeftRight = sensorLeftRight.getDistance();
  if(sensorUpDown.isCenter(distanceUpDown) && sensorLeftRight.isCenter(distanceLeftRight)){
    Config.gamePlayerIsInside = true;
  }
}

// not used method in the game because, even if the sensor are more precise, is harder for the player -> use for proffesional users :)

bool Game::areStabilizedDistances(int distanceUpDown, int distanceLeftRight)
{
  indexLastDistances ++;
  for(int index = 0 ; index < indexLastDistances ; index++){
    lastDistancesUpDown[index] = lastDistancesUpDown[index + 1];
    lastDistancesLeftRight[index] = lastDistancesLeftRight[index + 1];
  }
  lastDistancesUpDown[indexLastDistances] = distanceUpDown;
  lastDistancesLeftRight[indexLastDistances] = distanceLeftRight;
  
  if(indexLastDistances < 4){
    return false;
  }
  indexLastDistances = 4;

  int maxxDistanceUpDown = 0, maxxDistanceLeftRight = 0;
  int minnDistanceUpDown = 130, minnDistanceLeftRight = 130;
  for(int index = 0 ; index < indexLastDistances ; index++){
    maxxDistanceUpDown = max(maxxDistanceUpDown, lastDistancesUpDown[index]);
    maxxDistanceLeftRight = max(maxxDistanceLeftRight, lastDistancesLeftRight[index]);
    minnDistanceUpDown = min(minnDistanceUpDown, lastDistancesUpDown[index]);
    minnDistanceLeftRight = min(minnDistanceLeftRight, lastDistancesLeftRight[index]);
  }
  if(maxxDistanceUpDown - minnDistanceUpDown < EPSILON && maxxDistanceLeftRight - minnDistanceLeftRight < EPSILON){
    return true;
  }
  return false;
}

void Game::checkPosition(int pos){
  if(moves[currentMove] == pos){
    matrix.showRight();
    currentMove ++;
  }
  else{
    matrix.showWrong();
  }
  delay(100);
}

void Game::restart()
{
  Config.gamePlaying = false;
  Config.sensorUpDownCalibrated = Config.sensorLeftRightCalibrated = false;
  Config.gamePlayerIsInside = false;
  Config.gameCounterFinished = false;
}

void Game::getWinner()
{
  int maxScore = 0;
  for(int player = 1 ; player <= Config.numberOfPlayers ; player ++){
    if(Config.scores[player] > maxScore){
      maxScore = Config.scores[player];
      Config.gameWinner = player;
    }
    else if(Config.scores[player] == maxScore){
      Config.gameWinner = DRAW;
    }
  }
}

void Game::getLeaderBoard()
{
  int counter = 1;
  while(counter <= Config.numberOfPlayers){
     int maxScore = -1, indexPlayer;
     for(int player = 1 ; player <= Config.numberOfPlayers ; player ++){
        if(Config.scores[player] > maxScore){
          indexPlayer = player;
          maxScore = Config.scores[player];
        }
     }
     Config.leaderBoard[counter] = indexPlayer;
     Config.scores[indexPlayer] = (-1) * Config.scores[indexPlayer];
     counter ++;
  }
  for(int player = 1 ; player <= Config.numberOfPlayers ; player ++){
    Config.scores[player] = (-1) * Config.scores[player];
  }
}

void Game::resetGame()
{
    Config.gameFinished = true;
    Config.gameStarted = false;
}

#endif
