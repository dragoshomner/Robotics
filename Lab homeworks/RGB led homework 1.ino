const int potRedPin = A0;
const int potGreenPin= A1;
const int potBluePin = A2;

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

int potRed, potGreen, potBlue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(potRedPin, INPUT);
  pinMode(potGreenPin, INPUT);
  pinMode(potBluePin, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  potRed = analogRead(potRedPin);
  potGreen = analogRead(potGreenPin);
  potBlue = analogRead(potBluePin);
  
  int potRedValue = map(potRed, 0, 1023, 0, 255);
  int potGreenValue = map(potGreen, 0, 1023, 0, 255);
  int potBlueValue = map(potBlue, 0, 1023, 0 , 255);
  
  setColor(potRedValue, potGreenValue, potBlueValue);
  delay(1);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
