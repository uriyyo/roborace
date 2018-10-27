#ifndef Rangefinder_h
#define Rangefinder_h

class Rangefinder {
  public:
    virtual long getDistance() = 0;
};

class RangefinderDigital : public Rangefinder {
  private:
    int echoPin;
    int trigPin;
    int lastPosition;
  public:
    RangefinderDigital(int echoPin, int trigPin);

    virtual long getDistance();
};

RangefinderDigital::RangefinderDigital(int echoPin, int trigPin) {
  this->echoPin = echoPin;
  this->trigPin = trigPin;
  this->lastPosition = 0;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

long RangefinderDigital::getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  // Convert to cm
  long distance = (duration / 2) / 29.1;

//  if (distance >= 200 || distance <= 0) {
//    distance = lastPosition;
//  }else{
//    lastPosition = distance;
//  }
  
  return distance;
}

#endif
