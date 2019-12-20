#ifndef PAGES_H
#define PAGES_H

#define TITLE 0
#define CONTENT 1

#define SCROLL 0
#define SET_VALUE 1
#define SHOW 2

#define MAIN_MENU 0 
#define GAME 1 
#define HIGHSCORE 2
#define SETTINGS 3
#define INFO 4

#define STARTING_LEVEL 1 
#define DIFFICULTY 2

#define GAME_NO_OF_PLAYERS 0

#define GAME_CALIBRATING 0

#define PROCESSING_GAME 0

#define GAME_PLAYER_GO_INSIDE 0

#define GAME_FINISHED 0

// every screen has a corresponding number -> avoid hardcoding

#define MAIN_MENU_SCREEN 0 
#define START_GAME_SCREEN 1
#define HIGHSCORE_SCREEN 2
#define SETTINGS_SCREEN 3
#define INFO_SCREEN 4
#define GAME_NO_OF_PLAYERS_SCREEN 5
#define GAME_CALIBRATING_SCREEN 6
#define GAME_PLAYER_GO_INSIDE_SCREEN 7
#define PROCESSING_GAME_SCREEN 8
#define GAME_FINISHED_SCREEN 9
#define NEW_HIGHSCORE_SCREEN 10
#define RESULTS_SCREEN 11
#define RESTART_SCREEN 12
#define HIGHSCORE_SCREEN 13
#define SETTINGS_STARTING_LEVEL_SCREEN 14
#define SETTINGS_CHOOSE_DIFFICULTY_SCREEN 15

// children = number of elements to be displayed in content
// for instance, menu has 4 children: start game, settings, highscore, info

#define MAIN_MENU_CHILDREN 4
#define GAME_NO_OF_PLAYERS_CHILDREN 0
#define GAME_CALIBRATING_CHILDREN 0
#define PROCESSING_GAME_CHILDREN 0
#define GAME_PLAYER_GO_INSIDE_CHILDREN 0
#define GAME_FINISHED_CHILDREN 0
#define HIGHSCORE_CHILDREN 3
#define INFO_CHILDREN 4
#define SETTINGS_CHILDREN 2
#define SETTINGS_STARTING_LEVEL_CHILDREN 0
#define SETTINGS_CHOOSE_DIFFICULTY_CHILDREN 3

// there are three types of screen: SCROLL, SET_VALUE, SHOW
// SCROLL = a screen when I push the joystick up/down to get another information (e.g. menu)
// SET_VALUE = a screen when I push the joystick up/down to change the value (e.g. setting the number of players)
// SHOW = a screen with only informations

#define MAIN_MENU_TYPE SCROLL
#define GAME_NO_OF_PLAYERS_TYPE SET_VALUE
#define GAME_CALIBRATING_TYPE SHOW
#define GAME_PLAYER_GO_INSIDE_TYPE SHOW
#define PROCESSING_GAME_TYPE SHOW
#define GAME_FINISHED_TYPE SHOW
#define RESULTS_TYPE SCROLL
#define RESTART_TYPE SHOW
#define HIGHSCORE_TYPE SCROLL
#define INFO_TYPE SCROLL
#define SETTINGS_TYPE SCROLL
#define SETTINGS_STARTING_LEVEL_TYPE SET_VALUE
#define SETTINGS_CHOOSE_DIFFICULTY_TYPE SET_VALUE

#endif
