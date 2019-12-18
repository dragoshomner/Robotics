#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include "Pages.h"
#include "Joystick.h"

class Display: public LiquidCrystal{
  
   private: 
      Joystick joystick;
      const int displayWidth = 16;
      const int displayLines = 2;
      const char* menuTitle[5];
      const char* gameTitle[1];
      const char* calibratingTitle[1];
      const char* playerGoInside[1];
      const char* processingGameTitle[1];
      const char* gameFinishedTitle[1];
      const char* infoTitle[5];
      const char* settingsTitle[3];
      const char* difficultyTitle[4];
      int numberOfChildren;
      String title;
      String content;
      int currentChild;
      int currentScreen;
      int type;
      unsigned long lastTimeUpdated;
      
      void printTitle();
      void printContent();
      int nextChild();
      int previousChild();
      void increaseValue(int&, int, int);
      void decreaseValue(int&, int, int);
      void nextPage();
      void previousPage();
      
   public:
      Display(int, int, int, int, int, int);
      void initialize();
      void refresh();
      void update();
};


Display::Display(int RS, int enable, int d4, int d5, int d6, int d7) :
  LiquidCrystal(RS, enable, d4, d5, d6, d7){ 
    
  begin(displayWidth, displayLines);
    
  menuTitle[MAIN_MENU] = "Main Menu";
  menuTitle[GAME] = "Start Game";
  menuTitle[HIGHSCORE] = "Highscore";
  menuTitle[SETTINGS] = "Settings";
  menuTitle[INFO] = "Info";

  infoTitle[1] = "MemMove";
  infoTitle[2] = "by Homner Dragos";
  infoTitle[3] = "Git:dragoshomner";
  infoTitle[4] = "@UnibucRobotics";

  settingsTitle[1] = "Starting level";
  settingsTitle[2] = "Difficulty";

  difficultyTitle[EASY] = "Easy ";
  difficultyTitle[MEDIUM] = "Medium ";
  difficultyTitle[HARD] = "Hard ";

  gameTitle[GAME_NO_OF_PLAYERS] = "No. of players";

  calibratingTitle[GAME_CALIBRATING] = "Calibrating ...";

  playerGoInside[GAME_PLAYER_GO_INSIDE] = "Go inside";

  processingGameTitle[PROCESSING_GAME] = "Player ";

  gameFinishedTitle[GAME_FINISHED] = "Finished!";
  
  title = menuTitle[MAIN_MENU];
  currentScreen = MAIN_MENU_SCREEN;
  currentChild = GAME;
  numberOfChildren = MAIN_MENU_CHILDREN;
  type = MAIN_MENU_TYPE;
}

void Display::initialize()
{
  printTitle();
  printContent();
  lastTimeUpdated = millis();
}

void Display::update()
{
   int joystickY = joystick.YChanged();
   int joystickX = joystick.XChanged();
   
   if(joystickY == DOWN){
      if(type == SCROLL){
        currentChild = nextChild();
      }
      else if(type == SET_VALUE){
        if(currentScreen == GAME_NO_OF_PLAYERS_SCREEN){
          decreaseValue(Config.numberOfPlayers, 1, maximumNumberOfPlayers);
        }
        else if(currentScreen == SETTINGS_STARTING_LEVEL_SCREEN){
          decreaseValue(Config.startingLevel, 1, maximumNumberOfMoves);
        }
        else if(currentScreen == SETTINGS_CHOOSE_DIFFICULTY_SCREEN){
          decreaseValue(Config.difficulty, min(EASY, HARD), max(EASY, HARD));
          Config.bonusTimePerCompletedLevel = 1 + Config.difficulty;
        }
      }
      printContent();
   }
   if(joystickY == UP){
      if(type == SCROLL){
        currentChild = previousChild();
      }
      else if(type == SET_VALUE){
        if(currentScreen == GAME_NO_OF_PLAYERS_SCREEN){
          increaseValue(Config.numberOfPlayers, 1, maximumNumberOfPlayers);
        }
        else if(currentScreen == SETTINGS_STARTING_LEVEL_SCREEN){
          increaseValue(Config.startingLevel, 1, maximumNumberOfMoves);
        }
        else if(currentScreen == SETTINGS_CHOOSE_DIFFICULTY_SCREEN){
          increaseValue(Config.difficulty, min(EASY, HARD), max(EASY,HARD));
          Config.bonusTimePerCompletedLevel = 1 + Config.difficulty;
        }
      }
      printContent();
   }

   if(joystickX == RIGHT){
      nextPage();
   }
   else if(joystickX == LEFT){
      previousPage();
   }
}

void Display::refresh()
{
  if(currentScreen == PROCESSING_GAME_SCREEN){
    if(Config.gameNextPlayer){
      currentScreen = GAME_CALIBRATING_SCREEN;
      title = calibratingTitle[GAME_CALIBRATING];
      numberOfChildren = GAME_CALIBRATING_CHILDREN;
      type = GAME_CALIBRATING_TYPE;
      
      Config.gameNextPlayer = false;
      initialize();
    }
    
    else if(Config.gameFinished){
      currentScreen = GAME_FINISHED_SCREEN;
      title = gameFinishedTitle[GAME_FINISHED];

      Config.gameFinished = false;
      Config.gameStarted = false;
      Config.currentPlayer = 1;
      initialize();
    }

    if((unsigned long)millis() - lastTimeUpdated >= SECOND / 2){
      initialize();
    }
  }
  
  else if(currentScreen == GAME_CALIBRATING_SCREEN){
    if(Config.sensorUpDownCalibrated && Config.sensorLeftRightCalibrated){
      currentScreen = GAME_PLAYER_GO_INSIDE_SCREEN;
      title = playerGoInside[GAME_PLAYER_GO_INSIDE];
      numberOfChildren = GAME_PLAYER_GO_INSIDE_CHILDREN;
      type = GAME_PLAYER_GO_INSIDE_TYPE;
      
      initialize();
    }
  }

  else if(currentScreen == GAME_PLAYER_GO_INSIDE_SCREEN){
    if(Config.gamePlayerIsInside){
      currentScreen = PROCESSING_GAME_SCREEN;
      String player(Config.currentPlayer);
      title = processingGameTitle[PROCESSING_GAME] + player;
      numberOfChildren = PROCESSING_GAME_CHILDREN;
      type = PROCESSING_GAME_TYPE;

      initialize();
    }
  }
}

void Display::printTitle()
{
  setCursor(0, 0);
  print(EMPTY_LINE);
  setCursor(0, 0);
  print(title);
}

void Display::printContent()
{
  setCursor(0, 1);
  print(EMPTY_LINE);
  setCursor(0, 1);
  
  if(type == SCROLL){
    if(currentScreen == MAIN_MENU_SCREEN){
      content = ARROW + menuTitle[currentChild];
    }
    else if(currentScreen == RESULTS_SCREEN){
      String s1("Player "), s2(":"), s3(Config.scores[Config.leaderBoard[currentChild]]), s4(Config.leaderBoard[currentChild]);
      content = ARROW + s1 + s4 + s2 + s3;
    }
    else if(currentScreen == INFO_SCREEN){
      content = infoTitle[currentChild];
    }
    else if(currentScreen == SETTINGS_SCREEN){
      content = ARROW + settingsTitle[currentChild];
    }
    else if(currentScreen == HIGHSCORE_SCREEN){
      String s1(difficultyTitle[currentChild]), s2(Config.highscore[currentChild]);
      content = s1 + s2;
    }
  }
  
  else if(type == SET_VALUE){
    if(currentScreen == GAME_NO_OF_PLAYERS_SCREEN){
      content = Config.numberOfPlayers;
    }
    else if(currentScreen == SETTINGS_STARTING_LEVEL_SCREEN){
      content = Config.startingLevel;
    }
    else if(currentScreen == SETTINGS_CHOOSE_DIFFICULTY_SCREEN){
      content = difficultyTitle[Config.difficulty];
    }
  }

  else if(type == SHOW){
    if(currentScreen == GAME_CALIBRATING_SCREEN){
        content = EMPTY_LINE;
    }
    else if(currentScreen == PROCESSING_GAME_SCREEN){
        String s1("T:"), s2(Config.remainingTime), s3(" S:"), s4(Config.scores[Config.currentPlayer]);
        content = s1 + s2 + s3 + s4;
    }
    else if(currentScreen == GAME_FINISHED_SCREEN){
        if(Config.gameWinner < DRAW){
          if(Config.numberOfPlayers > 1){
            String s5("Player "), s6(Config.gameWinner), s7(" won!");
            content = s5 + s6 + s7;
          }
          else{
            String s5("Score: "), s6(Config.scores[1]);
            content = s5 + s6;
          }
        }
        else{
          String s8("Draw!");
          content = s8;
        }
    }
    else if(currentScreen == NEW_HIGHSCORE_SCREEN){
      content = Config.highscore[Config.difficulty];
    }
    else if(currentScreen == RESTART_SCREEN){
      content = "> Main menu";
    }
  }
  
  print(content);
}

int Display::nextChild()
{
  return currentChild < numberOfChildren ? currentChild + 1 : 1;
}

int Display::previousChild()
{
  return currentChild < 2 ? numberOfChildren : currentChild - 1;
}

void Display::increaseValue(int &value, int minVal, int maxVal)
{
  if(value < maxVal){
    value ++;
  }
}

void Display::decreaseValue(int &value, int minVal, int maxVal)
{
  if(value > minVal){
    value --;  
  }
}

void Display::nextPage()
{
  if(currentScreen == MAIN_MENU_SCREEN){
    if(currentChild == GAME){
      currentScreen = GAME_NO_OF_PLAYERS_SCREEN;
      title = gameTitle[GAME_NO_OF_PLAYERS];
      numberOfChildren = GAME_NO_OF_PLAYERS_CHILDREN;
      type = GAME_NO_OF_PLAYERS_TYPE;
    }
    else if(currentChild == HIGHSCORE){
      currentScreen = HIGHSCORE_SCREEN;
      title = "Highscore";
      numberOfChildren = HIGHSCORE_CHILDREN;
      type = HIGHSCORE_TYPE;
    }
    else if(currentChild == SETTINGS){
      currentScreen = SETTINGS_SCREEN;
      title = "Settings";
      numberOfChildren = SETTINGS_CHILDREN;
      type = SETTINGS_TYPE;
    }
    else if(currentChild == INFO){
      currentScreen = INFO_SCREEN;
      title = "Info";
      numberOfChildren = INFO_CHILDREN;
      type = INFO_TYPE;
    }
  }

  else if(currentScreen == GAME_NO_OF_PLAYERS_SCREEN){
    currentScreen = GAME_CALIBRATING_SCREEN;
    title = calibratingTitle[GAME_CALIBRATING];
    numberOfChildren = GAME_CALIBRATING_CHILDREN;
    type = GAME_CALIBRATING_TYPE;
    
    Config.gameStarted = true;
    
    for(int player = 0 ; player < 10 ; player ++){
      Config.scores[player] = 0;
    }
    Config.newHighscore = false;
  }

  else if(currentScreen == GAME_FINISHED_SCREEN){
    if(Config.newHighscore){
      title = "New Highscore";
      currentScreen = NEW_HIGHSCORE_SCREEN;
    }
    else{
      title = "Leaderboards";
      currentScreen = RESULTS_SCREEN;
      type = RESULTS_TYPE;
      numberOfChildren = Config.numberOfPlayers;
    }
  }

  else if(currentScreen == NEW_HIGHSCORE_SCREEN){
      title = "Leaderboards";
      currentScreen = RESULTS_SCREEN;
      type = RESULTS_TYPE;
      numberOfChildren = Config.numberOfPlayers;
  }

  else if(currentScreen == RESULTS_SCREEN){
    currentScreen = RESTART_SCREEN;
    title = "< Restart";
    type = RESTART_TYPE;
  }

  else if(currentScreen == RESTART_SCREEN){
    currentScreen = MAIN_MENU_SCREEN;
    title = menuTitle[MAIN_MENU];
    currentChild = GAME;
    numberOfChildren = MAIN_MENU_CHILDREN;
    type = MAIN_MENU_TYPE;
  }

  else if(currentScreen == SETTINGS_SCREEN){
    if(currentChild == STARTING_LEVEL){
      currentScreen = SETTINGS_STARTING_LEVEL_SCREEN;
      title = settingsTitle[STARTING_LEVEL];
      numberOfChildren = SETTINGS_STARTING_LEVEL_CHILDREN;
      type = SETTINGS_STARTING_LEVEL_TYPE;
    }
    else if(currentChild == DIFFICULTY){
      currentScreen = SETTINGS_CHOOSE_DIFFICULTY_SCREEN;
      title = settingsTitle[DIFFICULTY];
      numberOfChildren = SETTINGS_CHOOSE_DIFFICULTY_CHILDREN;
      type = SETTINGS_CHOOSE_DIFFICULTY_TYPE;
    }
  }

  currentChild = 1;

  initialize();
}

void Display::previousPage()
{
  if(currentScreen == RESTART_SCREEN){
      currentScreen = GAME_NO_OF_PLAYERS_SCREEN;
      title = gameTitle[GAME_NO_OF_PLAYERS];
      numberOfChildren = GAME_NO_OF_PLAYERS_CHILDREN;
      type = GAME_NO_OF_PLAYERS_TYPE;
  }

  // go back to menu
  else if(currentScreen == HIGHSCORE_SCREEN ||
      currentScreen == GAME_NO_OF_PLAYERS_SCREEN ||
      currentScreen == INFO_SCREEN ||
      currentScreen == SETTINGS_SCREEN){
    currentScreen = MAIN_MENU_SCREEN;
    title = menuTitle[MAIN_MENU];
    numberOfChildren = MAIN_MENU_CHILDREN;
    type = MAIN_MENU_TYPE;
  }

  // go back to settings
  else if(currentScreen == SETTINGS_STARTING_LEVEL_SCREEN ||
          currentScreen == SETTINGS_CHOOSE_DIFFICULTY_SCREEN){
    currentScreen = SETTINGS_SCREEN;
    title = "Settings";
    numberOfChildren = SETTINGS_CHILDREN;
    type = SETTINGS_TYPE;
  }
  
  currentChild = 1;

  initialize();
}

#endif
