#include "SevSeg.h"
#include "JC_Button.h"

const char 
  BLANK = ' ',
  DOT = '.';
const int
  digitOnInterval = 400,
  digitOffInterval = 200,
  joyThreshold = 200,
  joyMax = 1023,
  joyMin = 0;
const byte 
  joyButtonPin = 0,
  joyXPin = A0,
  joyYPin = A1,
  numDigits = 4;

SevSeg sevseg;
Button joyButton(joyButtonPin);

char 
  displayDigits[] = {'0', '0', '0', '0'},
  currentDigit = '0',
  displayContent[2 * numDigits];
unsigned long 
  lastTimeBlink;
unsigned int
  joyX,
  joyY,
  digitPosition,
  displayContentLength;
bool 
  digitOn = true,
  joyXChanged = false,
  joyYChanged = false,
  digitIsSet[] = {false, false, false, false};

// ..............................................................................

void setup() {
  Serial.begin(9600);

  initializeDisplay();
  initializeTimers();
  initializeJoyStick();
  
}

void loop() {

  readJoy();

  if(!digitIsSet[digitPosition]){
    joyPositionCheck();
    blinkDigit(digitPosition);
  }
  else{
    digitPosition = nextPosition(digitPosition);
    currentDigit = displayDigits[digitPosition];
  }
  
  joyButtonCheck();

  setDisplayDigits();
  
  sevseg.setChars(displayContent);
  
  sevseg.refreshDisplay();
}


// ..............................................................................

void initializeDisplay()
{
  byte digitPins[] = {5, 4, 3, 2};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  
  sevseg.setBrightness(0);
}

void initializeTimers()
{
  lastTimeBlink = millis();
}

void initializeJoyStick()
{
  //pinMode(joyButtonPin, INPUT_PULLUP);
  joyButton.begin();
}

// ..............................................................................

void blinkDigit(int index)
{
  if(digitOn){
    if((unsigned long)millis() - lastTimeBlink >= digitOnInterval){
      displayDigits[index] = BLANK;
      lastTimeBlink = millis();
      digitOn = !digitOn;
    }
  }
  else{
    if((unsigned long)millis() - lastTimeBlink >= digitOffInterval){
      displayDigits[index] = currentDigit;
      lastTimeBlink = millis();
      digitOn = !digitOn;
    }
  }
}

void refreshDigits()
{
  for(int i = 0 ; i < numDigits ; i ++){
    if(displayDigits[i] == BLANK){
      displayDigits[i] = currentDigit; 
    }
  }
}

char nextDigit(char c)
{
  int num = c - '0';
  num ++;
  if(num > 9){
    num = 0;
  }
  char result = num + '0';
  return result;
}

char previousDigit(char c){
  int num = c - '0';
  num --;
  if(num < 0){
    num = 9;
  }
  char result = num + '0';
  return result;
}

int nextPosition(int pos)
{
  for(int i = 0 ; i < numDigits ; i++){
    pos = (pos + 1) % numDigits;
    if(!digitIsSet[pos]){
      return pos;
    }
  }
  return 0;
}

int previousPosition(int pos)
{
  for(int i = 0 ; i < numDigits ; i++){
    pos = (pos - 1) % numDigits;
    if(pos < 0){
      pos = numDigits - 1;
    }
    if(!digitIsSet[pos]){
      return pos;
    }
  }
  return 0;
}

void readJoy()
{
  joyX = analogRead(joyXPin);
  joyY = analogRead(joyYPin);
}

void joyYPositionCheck(){
  if(joyMax - joyY <= joyThreshold){
    if(!joyYChanged){
       digitPosition = nextPosition(digitPosition);
       joyYChanged = true;
       
       refreshDigits();
       
       currentDigit = displayDigits[digitPosition];
    }
  }
  else if(joyY - joyMin <= joyThreshold){
    if(!joyYChanged){
      digitPosition = previousPosition(digitPosition);
      joyYChanged = true;

      refreshDigits();
      
      currentDigit = displayDigits[digitPosition];
    }
  }
  else{
    joyYChanged = false;
  }
}

void joyXPositionCheck()
{
  if(joyMax - joyX <= joyThreshold){
    if(!joyXChanged){
       displayDigits[digitPosition] = nextDigit(currentDigit);
       currentDigit = displayDigits[digitPosition];
       joyXChanged = true;
    }
  }
  else if(joyX - joyMin <= joyThreshold){
    if(!joyXChanged){
       displayDigits[digitPosition] = previousDigit(currentDigit);
       currentDigit = displayDigits[digitPosition];
       joyXChanged = true;
    }
  }
  else{
    joyXChanged = false;
  }
}

void joyPositionCheck()
{
  joyYPositionCheck();  
  joyXPositionCheck();
}

void joyButtonCheck()
{
  joyButton.read();
  if(joyButton.wasReleased()){
    digitIsSet[digitPosition] = true;
  }
}

void setDisplayDigits()
{
  for(int i = 0 ; i < 2 * numDigits ; i++)
  {
    displayContent[i] = BLANK;  
  }
  
  displayContentLength = 0;
  for(int i = 0 ; i < numDigits ; i++)
  {
    displayContent[displayContentLength ++] = displayDigits[i];
    if(digitIsSet[i]){
      displayContent[displayContentLength ++] = DOT;
    }
  }
}
