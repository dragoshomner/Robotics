#ifndef CONSTANTS_H
#define CONSTANTS_H

const int
  UP = 1,
  DOWN = 2,
  LEFT = 3,
  RIGHT = 4;

const int 
  EASY = 3,
  MEDIUM = 2,
  HARD = 1;

const int EPSILON = 20;

const String EMPTY_CHARACTER = "";
const String EMPTY_LINE = "                ";
const String ARROW = "> ";
const int SECOND = 1000;

const int
  calibratingSensorMin = 110,
  calibratingSensorMax = 150;

const int maximumNumberOfMoves = 20;
const int maximumNumberOfPlayers = 9;
const int DRAW = 101;

const int 
  matrixArrow[8][8] = {
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 1, 1, 1, 1, 0, 0},
    { 0, 1, 0, 1, 1, 0, 1, 0},
    { 1, 0, 0, 1, 1, 0, 0, 1},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0}
  },
  matrixRight[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 1, 0},
    { 0, 0, 0, 0, 0, 1, 0, 0},
    { 1, 0, 0, 0, 1, 0, 0, 0},
    { 0, 1, 0, 1, 0, 0, 0, 0},
    { 0, 0, 1, 0, 0, 0, 0, 0}
  },
  matrixWrong[8][8] = {
    { 1, 0, 0, 0, 0, 0, 0, 1},
    { 0, 1, 0, 0, 0, 0, 1, 0},
    { 0, 0, 1, 0, 0, 1, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 0, 1, 1, 0, 0, 0},
    { 0, 0, 1, 0, 0, 1, 0, 0},
    { 0, 1, 0, 0, 0, 0, 1, 0},
    { 1, 0, 0, 0, 0, 0, 0, 1}
  };



#endif
