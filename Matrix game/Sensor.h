#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
   private: 
      int echoPin;
      int trigPin;
      const int closeDistance = 40;
      const int centerDistance = 90;
      const int farDistance = 120;
      const int wallDistance = 110;
   public: 
      int getDistance();
      void initialize(int, int);
      bool isCalibrated();
      bool isCenter(int);
      bool isClose(int);
      bool isFar(int);
      bool isWall(int);
};

void Sensor::initialize(int _echoPin, int _trigPin)
{
  trigPin = _trigPin;
  echoPin = _echoPin;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

bool Sensor::isCalibrated()
{
  int distance = getDistance();
  if(distance >= calibratingSensorMin && distance <= calibratingSensorMax){
    return true;
  }
  return false;
}

int Sensor::getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration*0.034/2;
  return distance;
}

bool Sensor::isCenter(int distance)
{
  if(distance > closeDistance && distance < centerDistance){
    return true;
  }
  return false;
}

bool Sensor::isClose(int distance)
{
  if(distance < closeDistance){
    return true;
  }
  return false;
}

bool Sensor::isFar(int distance)
{
  if(distance > centerDistance && distance < farDistance){
    return true;
  }
  return false;
}

bool Sensor::isWall(int distance){
  if(distance > wallDistance){
    return true;
  }
  return false;
}

#endif
