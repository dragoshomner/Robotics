#include "JC_Button.h"
#include "SevSeg.h"
#include "Variables.h"
#include "Pins.h"
#include "Buttons.h"
#include "Sevsegs.h"
#include "Leds.h"
#include "App.h"

void setup() {
  initializeButtonsPins();

  initializeSevSeg();

  initializeSevSegText();

  initializeLEDs();
}

void loop() {
  refreshSevSegs();

  readButtons();

  updateApp();
}
