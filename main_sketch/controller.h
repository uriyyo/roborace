#ifndef Controller_h
#define Controller_h

#define TURN_DELAY 250
#define BACKWARD_DELAY 1000
#define MAX_DISTANCE 20
#define MIN_DISTANCE 10

#include "rangefinder.h"

enum TurnType {
  LEFT_TURN,
  RIGHT_TURN,
  NO_TURN,
  MAX_TURN_STATE
};

int turn_delays[MAX_TURN_STATE] = {
  1000, // LEFT
  1000, // RIGTH
  0
};

enum MoveType {
  FRONT,
  BACKWARD,
  MAX_MOVE_STATE
};

// int move_delays[MAX_MOVE_STATE] = {
//   0,
//   1000
// }

class Controller {
  private:
    Rangefinder *front;
    Rangefinder *left;
    Rangefinder *right;
    Car* car;

    TurnType turn_type;
    MoveType move_type;
    unsigned long last_time_milis;
    TurnType getNextStateTurn(long front_distance, long left_distance, long right_distance);

  public:
    Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right, Car* car);

    void move();
};

Controller::Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right, Car* car) {
  this->front = front;
  this->left = left;
  this->right = right;
  this->car = car;
  this->turn_type = NO_TURN;
  this->move_type = FRONT;
}

TurnType Controller::getNextStateTurn(long front_distance, long left_distance, long right_distance)
{
  if (front_distance < MAX_DISTANCE)
  {
    if (left_distance < right_distance)
      return RIGHT_TURN;
    else 
      return LEFT_TURN;
  }
  else 
  {
      if (left_distance < MIN_DISTANCE)
        return RIGHT_TURN;
      else if (right_distance < MIN_DISTANCE)
        return LEFT_TURN;
      return NO_TURN;
  }
}


void Controller::move() {
  // TODO: move magic numbers to constants
  long left_distance = left->getDistance();
  long right_distance = right->getDistance();
  long front_distance = front->getDistance();
  car->Forward();
  switch (turn_type) 
  {
    case NO_TURN:
      turn_type = getNextStateTurn(front_distance, left_distance, right_distance);
      if (turn_type != NO_TURN)
        last_time_milis = millis();
      else
        car->CancelTurn();
      break;
     case LEFT_TURN:
      if ( millis() - last_time_milis >= turn_delays[turn_type])
        turn_type = NO_TURN;
      else
        car->Left();
     break;
     case RIGHT_TURN:
      if ( millis() - last_time_milis >= turn_delays[turn_type])
        turn_type = NO_TURN;
      else
        car->Right();
     break;
  }

}

#endif
