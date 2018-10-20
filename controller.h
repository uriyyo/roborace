#ifndef Controller_h
#define Controller_h

#include "Rangefinder\rangefinder.h"

class Controller {
  private:
    Rangefinder *front;
    Rangefinder *left;
    Rangefinder *right;
    // TODO: add pointer on Car instance
  public:
    Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right);

    void move();
};

Controller::Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right) {
  this->front = front;
  this->left = left;
  this->right = right;
}

void Controller::move() {
  // TODO: move magic numbers to constants
  long left_distance = left->getDistance();
  long right_distance = right->getDistance();
  long front_distance = front->getDistance();

  if (abs(right_distance - left_distance) < 4) {
    Serial.println("No turn");
  } else if (right_distance > left_distance || right_distance == -1) {
    Serial.println("Rigth");
  } else {
    Serial.println("Left");
  }

  if (front_distance < 5) {
    Serial.println("Wall is near");
  }

}

#endif
