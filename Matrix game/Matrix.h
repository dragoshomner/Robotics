#ifndef MATRIX_H
#define MATRIX_H

#include "LedControl.h"

class Matrix : public LedControl{
    private:
      void showThree();
      void showTwo();
      void showOne();
    public: 
      Matrix();
      void initialize();
      void showCounter();
      void showDirection(int);
      void showDot();
      void showRight();
      void showWrong();
      void showBlank();
      void showFinished();
};

Matrix::Matrix() :
  LedControl(MATRIX_PINS.din, MATRIX_PINS.clk, MATRIX_PINS.load)
{
}

void Matrix::initialize()
{
  shutdown(0, false);
  setIntensity(0, 2);
  clearDisplay(0);
}

// counter -> want to freeze the system while it is displayed (no reads, writes, movements)

void Matrix::showCounter(){
  showThree();
  delay(1000);
  showTwo();
  delay(1000);
  showOne();
  delay(1000);
  showDot();
  delay(1000);
}

// used this way of printing because, firstly, I had a 2D array for every number, but not enough memory :) 

void Matrix::showDot()
{
  showBlank();
  setLed(0, 2, 2, true);
  setLed(0, 2, 3, true);
  setLed(0, 2, 4, true);
  setLed(0, 2, 5, true);
  
  setLed(0, 3, 2, true);
  setLed(0, 3, 3, true);
  setLed(0, 3, 4, true);
  setLed(0, 3, 5, true);
  
  setLed(0, 4, 2, true);
  setLed(0, 4, 3, true);
  setLed(0, 4, 4, true);
  setLed(0, 4, 5, true);
  
  setLed(0, 5, 2, true);
  setLed(0, 5, 3, true);
  setLed(0, 5, 4, true);
  setLed(0, 5, 5, true);
}

void Matrix::showThree(){
  showBlank();
  setLed(0, 1, 2, true);
  setLed(0, 1, 3, true);
  setLed(0, 1, 4, true);
  setLed(0, 1, 5, true);
  setLed(0, 2, 5, true);
  setLed(0, 3, 5, true);
  setLed(0, 4, 5, true);
  setLed(0, 5, 5, true);
  setLed(0, 6, 5, true);
  setLed(0, 7, 5, true);
  setLed(0, 4, 2, true);
  setLed(0, 4, 3, true);
  setLed(0, 4, 4, true);
  setLed(0, 7, 2, true);
  setLed(0, 7, 3, true);
  setLed(0, 7, 4, true);
}

void Matrix::showTwo(){
  showBlank();
  setLed(0, 1, 2, true);
  setLed(0, 1, 3, true);
  setLed(0, 1, 4, true);
  setLed(0, 1, 5, true);
  setLed(0, 2, 5, true);
  setLed(0, 3, 5, true);
  setLed(0, 4, 5, true);
  setLed(0, 4, 4, true);
  setLed(0, 4, 3, true);
  setLed(0, 4, 2, true);
  setLed(0, 5, 2, true);
  setLed(0, 6, 2, true);
  setLed(0, 7, 2, true);
  setLed(0, 7, 3, true);
  setLed(0, 7, 4, true);
  setLed(0, 7, 5, true);
}

void Matrix::showOne(){
  showBlank();
  setLed(0, 1, 5, true);
  setLed(0, 2, 5, true);
  setLed(0, 3, 5, true);
  setLed(0, 4, 5, true);
  setLed(0, 5, 5, true);
  setLed(0, 6, 5, true);
  setLed(0, 7, 5, true);
}

void Matrix::showRight(){
  for(int row = 0 ; row < 8 ; row++){
    for(int col = 0 ; col < 8 ; col++){
      setLed(0, row, col, matrixRight[row][col]);
    }
  }
}

void Matrix::showWrong(){
  for(int row = 0 ; row < 8 ; row++){
    for(int col = 0 ; col < 8 ; col++){
      setLed(0, row, col, matrixWrong[row][col]);
    }
  }
}

void Matrix::showBlank()
{
  for(int row = 0 ; row < 8 ; row ++){
    for(int col = 0 ; col < 8 ; col ++){
      setLed(0, row, col, 0);
    }
  }
}

// one method used for all 4 directions and only one matrix, to avoid initializing one matrix for every arrow (too small dynamic memory :( )

void Matrix::showDirection(int moveDirection)
{
  for(int row = 0 ; row < 8 ; row ++){
    for(int col = 0 ; col < 8 ; col++){
      switch(moveDirection){
        case UP:
          setLed(0, row, col, matrixArrow[row][col]);
          break;
        case RIGHT:
          setLed(0, row, col, matrixArrow[7 - col][row]);
          break;
        case LEFT:
          setLed(0, row, col, matrixArrow[col][row]);
          break;
        case DOWN:
          setLed(0, row, col, matrixArrow[7 - row][col]);
          break;
      }
    }
  }
}

void Matrix::showFinished()
{
  for(int row = 0 ; row < 8 ; row ++){
    for(int col = 0 ; col < 8 ; col ++){
      setLed(0, row, col, matrixArrow[row][col] || matrixArrow[7-col][row] || matrixArrow[col][row] || matrixArrow[7-row][col]);
    }
  }
}

#endif
