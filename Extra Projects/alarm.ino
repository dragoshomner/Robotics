#include "SevSeg.h"
SevSeg sevseg; 

unsigned int currentTime, previousTime;
unsigned int counterDisplay = 0;
const int second = 1000;
const int waitingTimeStatingCountDown = 3;

int joyStickButtonPin = 4;
int joyStickPin_X = A0;
int joyStickPin_Y = A1;
int joyStickButtonValue, joyStickButtonTime, joyStickTime;
int joyStickValue_X, joyStickValue_Y;
int joyStickPreviousValue_X, joyStickPreviousValue_Y;
const int joyStickInterval = 250;

bool startTimer = false;
int lastTimeCounterChanged;
int previousTimeDownCounter;

int buzzerPin = 10;
int buzzerTone = 500;
int buzzerDuration = 1500;

void initialize4Digits()
{
  byte numDigits = 4;
  byte digitPins[] = {0, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void initializeJoystick()
{
  pinMode(joyStickButtonPin, INPUT);
}

void initializeBuzzer()
{
  pinMode(buzzerPin, OUTPUT);
}

void changeDisplayCounter(int value, int interval)
{
  value = (!counterDisplay && value < 0) ? 0 : value;
  currentTime = millis();
  lastTimeCounterChanged = currentTime;
  if(currentTime - previousTime >= interval && value)
  {
    previousTime = currentTime;
    counterDisplay += value;
    sevseg.setNumber(counterDisplay);
    Serial.println(counterDisplay);
  }
}

void setStartingTime()
{
    joyStickValue_X = analogRead(joyStickPin_X);

    if(millis() - joyStickTime >= joyStickInterval){
      if(joyStickValue_X == 0 || joyStickValue_X == 1023){
        int value = joyStickValue_X ? -1 : 1;
        changeDisplayCounter(value, joyStickInterval);
      }
    }
}

void playAlarm()
{
   tone(buzzerPin, buzzerTone, buzzerDuration);
   delay(buzzerDuration);
}

void startCountingDown()
{
  if(millis() - previousTimeDownCounter >= second){
    changeDisplayCounter(-1, second);
    previousTimeDownCounter = millis();
    if(counterDisplay == 0){
      startTimer = false;
      playAlarm();
    }
  }
}

void setup(){
  Serial.begin(9600);
  initialize4Digits();
  initializeJoystick();
  initializeBuzzer();
}

void loop(){
    if(millis() - lastTimeCounterChanged >= waitingTimeStatingCountDown * second && counterDisplay){
      startTimer = true;
    }
    
    if(startTimer){
      startCountingDown();
    }
    else{
      setStartingTime();
    }
    
    sevseg.refreshDisplay();
    delay(1);
}
