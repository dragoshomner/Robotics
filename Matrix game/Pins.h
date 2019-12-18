#ifndef PINS_H
#define PINS_H

const struct DisplayPins{
  int RS = 7;
  int enable = 6;
  int d4 = 5;
  int d5 = 4;
  int d6 = 3;
  int d7 = 2;
} DISPLAY_PINS;

const struct JoystickPins{
  int X = A1;
  int Y = A0;
} JOYSTICK_PINS;

const struct SensorUpDownPins{
  int echo = 8;
  int trig = 9;
} SENSOR_UP_DOWN_PINS;

const struct SensorLeftRightPins{
  int echo = A2;
  int trig = 13;
} SENSOR_LEFT_RIGHT_PINS;

const struct MatrixPins{
  int din = 12;
  int clk = 11;
  int load = 10;
} MATRIX_PINS;

#endif
