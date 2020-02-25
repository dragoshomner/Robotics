#ifndef LEDS_H
#define LEDS_H

void initializeLEDs() {
  digitalWrite(playerOneCorrectPin, LOW);
  digitalWrite(playerOneWrongPin, LOW);
  digitalWrite(playerTwoCorrectPin, LOW);
  digitalWrite(playerTwoWrongPin, LOW);
}

void lightLed(int turnOnLedPin, int turnOffLedPin) {
  digitalWrite(turnOnLedPin, HIGH);
  digitalWrite(turnOffLedPin, LOW);
}



#endif
