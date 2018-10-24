#ifndef Controller_h
#define Controller_h

#include "rangefinder.h"

class Controller {
  private:
    Rangefinder *front;
    Rangefinder *left;
    Rangefinder *right;
    Car* car;
  public:
    Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right, Car* car);

    void move();
};

Controller::Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right, Car* car) {
  this->front = front;
  this->left = left;
  this->right = right;
  this->car = car;
}

void Controller::move() {
  // TODO: move magic numbers to constants
  long left_distance = left->getDistance();
  long right_distance = right->getDistance();
  long front_distance = front->getDistance();

  // Analyze distance from front rangefinder
  if (front_distance > 20) {
    car->Forward();
  }
  // Need to slow down before turn
  else if (front_distance < 20 && front_distance > 5) {
    car->Forward(200);
  }
  // In this case we stand in wall front
  else {
    // Move backward for 1 second, than try to move again
    car->Backward();
    delay(1000);
    move();
    return;
  }

  if (abs(right_distance - left_distance) < 5) {
    car->CancelTurn();
  } else if (right_distance > left_distance) {
    car->Right();
    delay(250);
  } else {
    car->Left();
    delay(250);
  }
}

#endif
