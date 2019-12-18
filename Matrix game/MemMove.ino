#include "App.h"

App app;

void setup() {
  Serial.begin(9600);
  EEPROM.write(0, 0); 
  EEPROM.write(1, 0); 
  EEPROM.write(2, 0); 
  app.initialize();
}

void loop() {
  app.update();
}
