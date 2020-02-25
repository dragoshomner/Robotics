#ifndef SEVSEGS_H
#define SEVSEGS_H

SevSeg 
  sevsegPlayerOne, 
  sevsegPlayerTwo;

void initializeSevSeg() {
  byte numDigits = 4;
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  // player One
  byte digitPinsPlayerOne[] = {43, 45, 46, 49};
  byte segmentPinsPlayerOne[] = {48, 44, 41, 39, 38, 47, 42, 40};
  sevsegPlayerOne.begin(hardwareConfig, numDigits, digitPinsPlayerOne, segmentPinsPlayerOne, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);

  
  byte digitPinsPlayerTwo[] = {7, 9, 10, 13};
  byte segmentPinsPlayerTwo[] = {12, 8, 5, 3, 2, 11, 6, 4};
  sevsegPlayerTwo.begin(hardwareConfig, numDigits, digitPinsPlayerTwo, segmentPinsPlayerTwo, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
}

void initializeSevSegText() {
  strcpy(textPlayerOne, defaultText);
  strcpy(textPlayerTwo, defaultText);
}

void setSevSegText(char *text, char answer) {
  if (answer == 'A') {
    strcpy(text, "   A");
  }
  if (answer == 'B') {
    strcpy(text, "  8 ");
  }
  if (answer == 'C') {
    strcpy(text, " C  ");
  }
  if (answer == 'D') {
    strcpy(text, "0   ");
  }
}

void refreshSevSegs() {
  sevsegPlayerOne.setChars(textPlayerOne);
  sevsegPlayerTwo.setChars(textPlayerTwo);
  sevsegPlayerOne.refreshDisplay();
  sevsegPlayerTwo.refreshDisplay();
}

#endif
