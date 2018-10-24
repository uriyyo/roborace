#ifndef Controller_h
#define Controller_h

#include "rangefinder.h"

class Controller {
  private:
    Rangefinder *front;
    Rangefinder *left;
    Rangefinder *right;
    Car* car;
    // TODO: add pointer on Car instance
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

  if (front_distance < 10){
    car->Stop();
  }else{
//    car->Forward();
  }

//  if (abs(right_distance - left_distance) < 5) {
//    car->CancelTurn();
//  } else if (right_distance > left_distance) {
//    car->Right();
//  } else {
//    car->Left();
//  }
  if (left_distance < 20){
    car->Right();
  } else if (left_distance != 20){
    car->Left();
  } else {
     car->CancelTurn();
  }

}

#endif
