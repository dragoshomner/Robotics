#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Pins.h"

// used class, coded from scratch, to return the movement of the joystick using constants UP, DOWN, LEFT, RIGHT

class Joystick{
  private:
    const int joyThreshold = 200;
    const int JOY_MIN = 0;
    const int JOY_MAX = 1023;
    
    int 
      joyXValue,
      joyYValue,
      joyXDirection,
      joyYDirection;
    
    bool
     joyYTriggered = false,
     joyXTriggered = false;
  
  public:
    int XChanged();
    int YChanged();
};

// 0 = no ; 1 = up ; 2 = down
int Joystick::YChanged()
{
  joyYValue = analogRead(JOYSTICK_PINS.Y);

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
int Joystick::XChanged()
{
  joyXValue = analogRead(JOYSTICK_PINS.X);

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

#endif
