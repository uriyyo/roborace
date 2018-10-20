#ifndef Rangefinder_h
#define Rangefinder_h


class Rangefinder {
private:
    int echoPin;
    int trigPin;
public:
    Rangefinder(int echoPin, int trigPin);

    long getDistance();
};

Rangefinder::Rangefinder(int echoPin, int trigPin) {
    this->echoPin = echoPin;
    this->trigPin = trigPin;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long Rangefinder::getDistance() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    // Convert to cm
    long distance = (duration / 2) / 29.1;

    if (distance >= 200 || distance <= 0) {
        return -1;
    }

    return distance;
}

#endif