#ifndef APP_H
#define APP_H

#include "EEPROM.h"
#include "Pins.h"
#include "Constants.h"
#include "Config.h"
#include "Display.h"
#include "Game.h"

class App{
  private: 
    Display *display;
    Game game;
  public:
    App();
    void initialize();
    void update();
};

App::App(){}

void App::initialize(){
   display = new Display(
      DISPLAY_PINS.RS,
      DISPLAY_PINS.enable,
      DISPLAY_PINS.d4,
      DISPLAY_PINS.d5,
      DISPLAY_PINS.d6,
      DISPLAY_PINS.d7
    );
    
    display->initialize();
    game.initialize();

    Config.highscore[EASY] = EEPROM.read(0);
    Config.highscore[MEDIUM] = EEPROM.read(1);
    Config.highscore[HARD] = EEPROM.read(2);
}

void App::update(){
  display->update();

  // Config.gameStarted is true after the number of player is selected, and now, the user cannot go back to menu until he finishes the game
  if(Config.gameStarted){
    game.update();
    display->refresh();
  }
}

#endif
