#include "LiquidCrystal.h"
#include "JC_Button.h"
#include "EEPROM.h"

const char
  CURSOR = '>',
  EMPTY = ' ',
  EMPTY_LINE[17] = "                ";
const int 
  UP = 1,
  DOWN = 2, 
  LEFT = 1,
  RIGHT = 2;
const int 
  SECOND = 1000;
const int
  RS = 12,
  enable = 11,
  d4 = 5,
  d5 = 4,
  d6 = 3,
  d7 = 2;
const int
  joyButtonPin = 8,
  joyXPin = A0,
  joyYPin = A1,
  joyThreshold = 100,
  JOY_MAX = 1023,
  JOY_MIN = 0;
const int
  numMenuItems = 3;
const int
  gameFinishTime = 10 * SECOND,
  levelIncrementTime = 5 * SECOND;

char
  menuText[numMenuItems + 1][16] = {" Start Game", " Highscore", " Options", " "};

String
  userName = "",
  readUserName = "";

int
  currentMenuItem,
  joyXValue,
  joyYValue,
  joyYDirection,
  joyXDirection;

bool 
  joyYTriggered = false,
  joyXTriggered = false;
bool
  gameIsFinished = false,
  gameIsRunning = false;
bool
  userNameReadCompleted = false;
unsigned long 
  highscoreValue,
  score,
  level,
  startingLevel = 0,
  gameCurrentTime,
  gameStartingTime,
  startingLetterToShow,
  lastTimeScrolled,
  lastTimeLevelIncrement;
int posX,
    posY;

enum Screen { menu, game, highscore, options, finishedGame};
Screen currentScreen = menu;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);
Button joyButton(joyButtonPin);

// .......................................................................................................................

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  joyButton.begin();

  highscoreValue = EEPROM.read(0);
  initializeMenuItems();
}

void loop() {
  manageTabs();
}

// .......................................................................................................................

void goToMenu()
{
  currentScreen = menu;
  initializeMenuItems();
}

void goToGame()
{
  currentScreen = game;
  level = startingLevel;
  initializeGameItems();
}

void goToHighscore()
{
  currentScreen = highscore;
  initializeHighScoreItems();
}

void goToOptions()
{
  currentScreen = options;
  initializeOptionsItems();
}

void goToFinishedGame()
{
  currentScreen = finishedGame;
  initializeFinishedGameItems();
}

void manageTabs()
{
  posX = joyXChanged();
  posY = joyYChanged(); 
  
  joyButton.read();
  if(currentScreen == menu){
    menuUpdate();

    if(posX == RIGHT){
      if(currentMenuItem == 0){
        goToGame();
      }
      else if(currentMenuItem == 1){
        goToHighscore();
      }
      else if(currentMenuItem == 2){
        goToOptions();
      }
    }
  }
  
  else if(currentScreen == game){
    runGame();
  }
  
  else if(currentScreen == highscore){
    if(posX == LEFT){
      goToMenu();
    }
    if(joyButton.wasReleased()){
      resetHighscore();
    }
  }

   else if(currentScreen == options){
    if(posX == LEFT){
      currentScreen = menu;
      initializeMenuItems();
    }
    
    if(posY == UP){
      if(startingLevel < 99){
        startingLevel = startingLevel + 1;
        updateStartingLevel();
      }
    }
    
    if(posY == DOWN){
      if(startingLevel > 0){
        startingLevel = max(startingLevel - 1,  0);
        updateStartingLevel();
      }
    }

    if(Serial.available() > 0){
      char incomingByte = Serial.read();
      
      if(incomingByte == '\n'){
        userName = readUserName;
        updateUserName();
        readUserName = "";
      }
      else{
        readUserName += incomingByte;
      }
    }
  }

  else if(currentScreen == finishedGame){
    if((unsigned long)millis() - lastTimeScrolled > 500){
      lastTimeScrolled = millis();
      char text[100] = "  You finished the game. Press button to exit.";
      startingLetterToShow = (startingLetterToShow + 1) % strlen(text);
      scrollText(text);
    }

    if(joyButton.wasReleased()){
      goToMenu();
    }
  }
}

void initializeMenuItems()
{
  updateCurrentMenuItem();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuText[currentMenuItem]);
  lcd.setCursor(0, 1);
  lcd.print(menuText[currentMenuItem + 1]);
}

void initializeGameItems(){
  score = 3 * level;
  
  char firstLine[16] = "Lives:3 Level:",
        secondLine[16] = "Score:";
  char levelString[2], scoreString[3];
  
  itoa(level, levelString, 10);
  strcat(firstLine, levelString);
  itoa(score, scoreString, 10);
  strcat(secondLine, scoreString);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}

void initializeFinishedGameItems()
{
  startingLetterToShow = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Congratulations!");
}

void initializeHighScoreItems(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Highscore:");
  lcd.setCursor(0, 1);
  char highscoreString[3];
  itoa(highscoreValue, highscoreString, 10);
  lcd.print(highscoreString);
}

void initializeOptionsItems(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  
  updateStartingLevel();
  updateUserName();
}

void updateCurrentMenuItem()
{
  int index;
  for(index = 0 ; index < 3 ; index++){
    menuText[index][0] = EMPTY;
  }
  menuText[currentMenuItem][0] = CURSOR;
}

// 0 = no ; 1 = up ; 2 = down
int joyYChanged()
{
  joyYValue = analogRead(joyYPin);

  if(JOY_MAX - joyYValue < joyThreshold){
     joyYTriggered = true;
     joyYDirection = DOWN;
  }
  else if(joyYValue - JOY_MIN < joyThreshold){
    joyYTriggered = true;
    joyYDirection = UP;
  }
  else if(joyYTriggered){
    joyYTriggered = false;
    return joyYDirection;
  }
  else{
    joyYDirection = 0;
  }
  return 0;
}

// 0 = no ; 1 = left ; 2 = right
int joyXChanged()
{
  joyXValue = analogRead(joyXPin);

  if(JOY_MAX - joyXValue < joyThreshold){
     joyXTriggered = true;
     joyXDirection = LEFT;
  }
  else if(joyXValue - JOY_MIN < joyThreshold){
    joyXTriggered = true;
    joyXDirection = RIGHT;
  }
  else if(joyXTriggered){
    joyXTriggered = false;
    return joyXDirection;
  }
  else{
    joyXDirection = 0;
  }
  return 0;
}

void menuUpdate()
{
  if(posY == UP){
    currentMenuItem  = max(0, currentMenuItem - 1);
  }
  if(posY == DOWN){
    currentMenuItem = min(numMenuItems - 1, currentMenuItem + 1); 
  }
  if(posY > 0){
    initializeMenuItems();
  }
}

void runGame()
{
  if(!gameIsRunning){
    level = startingLevel;
    gameIsRunning = true;
    gameStartingTime = millis();
    lastTimeLevelIncrement = millis();
  }
  
  gameCurrentTime = (millis() - gameStartingTime) / SECOND;
  
  if((unsigned long)millis() - gameStartingTime >= gameFinishTime && gameIsRunning){
    gameIsRunning = false;
    lastTimeScrolled = millis();
    updateHighscore();
    goToFinishedGame();
  }

  if((unsigned long)millis() - lastTimeLevelIncrement >= levelIncrementTime && gameIsRunning){
    lastTimeLevelIncrement = millis();
    updateLevel();
  }

}

void updateHighscore()
{
  if(score > highscoreValue){
    highscoreValue = score;
    EEPROM.write(0, highscoreValue);
  }
}

void resetHighscore()
{
  EEPROM.write(0, 0);
  highscoreValue = 0;
  initializeHighScoreItems();
}

void updateLevel()
{
    level ++;
    score = level * 3;
    
    lcd.setCursor(14, 0);
    char levelString[3];
    itoa(level, levelString, 10);
    lcd.print(levelString); 

    lcd.setCursor(6, 1);
    char scoreString[3];
    itoa(score, scoreString, 10);
    lcd.print(scoreString);
}

void scrollText(char *text)
{
  int len = strlen(text);
  lcd.setCursor(0, 1);

  int lcdColumn = 0;
  for(int i = startingLetterToShow ; i < min(len, 16 + startingLetterToShow) ; i++){
    lcd.print(text[i]);
    lcd.setCursor(lcdColumn++, 1);
  }

  if(lcdColumn < 16){
    for(int i = lcdColumn; i <= 16 ; i++){
      lcd.print(EMPTY);
      lcd.setCursor(lcdColumn++, 1);
    }
  }
}

void updateStartingLevel()
{
  lcd.setCursor(0, 0);
  lcd.print(EMPTY_LINE);
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.setCursor(6, 0);
  char startingLevelString[3];
  itoa(startingLevel, startingLevelString, 10);
  lcd.print(startingLevelString);
}

void updateUserName()
{
  lcd.setCursor(0, 1);
  lcd.print(EMPTY_LINE);
  lcd.setCursor(0, 1);
  lcd.print(userName);  
}
