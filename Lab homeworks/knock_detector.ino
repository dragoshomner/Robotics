#include <JC_Button.h>

const int SECOND = 1000;

const byte 
  PASIVE_BUZZER_PIN = A0,
  ACTIVE_BUZZER_PIN = A1,
  BUTTON_PIN = 2;

const int 
  pasiveBuzzerThreshold = 10,
  activeBuzzerValue = 1000,
  activeBuzzerDelay = 5;

Button 
  button(BUTTON_PIN);

bool 
  buzzerWasKnocked = false,
  songStarted = false;

int pasiveBuzzerValue;
unsigned int previousTimeKnocked;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  pinMode(PASIVE_BUZZER_PIN, INPUT);
  pinMode(ACTIVE_BUZZER_PIN, OUTPUT);

  button.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  button.read();
  
  if(button.wasReleased() && songStarted){
    buzzerWasKnocked = false;
    stopSong(ACTIVE_BUZZER_PIN);
  }
  
  if(isKnocked(PASIVE_BUZZER_PIN)){
    buzzerWasKnocked = true;
    resetTimer();
  }

  if(timerIsFinished(previousTimeKnocked, activeBuzzerDelay * SECOND) && buzzerWasKnocked){
    startSong(ACTIVE_BUZZER_PIN);
    songStarted = true;
  }
}

bool isKnocked(int pin)
{
  pasiveBuzzerValue = analogRead(pin);
  if(pasiveBuzzerValue > pasiveBuzzerThreshold){
    return true;
  }
  return false;
}

void resetTimer()
{
    previousTimeKnocked = millis();
}

bool timerIsFinished(int start, int duration)
{
  if(millis() - start >= duration){
    return true;
  }
  return false;
}

void startSong(int pin)
{
  tone(pin, activeBuzzerValue);
}

void stopSong(int pin)
{
  songStarted = false;
  noTone(pin);
}
