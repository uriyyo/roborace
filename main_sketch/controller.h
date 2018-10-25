#ifndef Controller_h
#define Controller_h
#include "rangefinder.h"

#define FRONT_NORMAL_SPEED 160
#define FRONT_SLOW_SPEED 130

#define TURN_DELAY 250
#define MIN_DELAY 0

#define BACKWARD_DELAY 1200
#define BACKWARD_TIMEOUT 500

#define MAX_DISTANCE 25
#define MIN_DISTANCE 7


enum TurnType {
  LEFT_TURN,
  RIGHT_TURN,
  NO_TURN,
  MAX_TURN_STATE
};

int turn_delays[MAX_TURN_STATE] = {
  TURN_DELAY,
  TURN_DELAY,
  MIN_DELAY
};

enum MoveType {
  FRONT,
  FRONT_SLOW,
  BACKWARD,
  MAX_MOVE_STATE
};

 int move_delays[MAX_MOVE_STATE] = {
   MIN_DELAY,
   MIN_DELAY,
   BACKWARD_DELAY
 };

class Controller {
  private:
    Rangefinder *front;
    Rangefinder *left;
    Rangefinder *right;
    Car* car;

    TurnType turn_type;
    MoveType move_type;
    unsigned long last_time_milis;
    unsigned long last_move_time_millis;
    TurnType getNextStateTurn(long front_distance, long left_distance, long right_distance);
    MoveType getNextStateMove(long front_distance);

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
  }

  return NO_TURN;
}

MoveType Controller::getNextStateMove(long front_distance)
{
    if (front_distance < MIN_DISTANCE){
        return BACKWARD;
    } else if (front_distance < MAX_DISTANCE){
        return FRONT_SLOW;
    }else {
        return FRONT;
    }
}

void Controller::move() {
  long left_distance = left->getDistance();
  long right_distance = right->getDistance();
  long front_distance = front->getDistance();

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
      else{
          // FIXME: move to function
          if (move_type == BACKWARD)
              car->Right();
          else
              car->Left();
      }
     break;
     case RIGHT_TURN:
      if ( millis() - last_time_milis >= turn_delays[turn_type])
        turn_type = NO_TURN;
      else{
          if (move_type == BACKWARD)
            car->Left();
          else
            car->Right();
      }
     break;
  }

  if (move_type == BACKWARD){
      if (millis() - last_move_time_millis >= move_delays[move_type])
          move_type = FRONT;
      else
          car->Backward(FRONT_NORMAL_SPEED);
  } else{
      if (move_type == FRONT){
          car->Forward(FRONT_NORMAL_SPEED);
      }else{
          car->Forward(FRONT_SLOW_SPEED);
      }

      move_type = getNextStateMove(front_distance);

      if (move_type == BACKWARD){
          car->Stop();
          delay(BACKWARD_TIMEOUT);

          last_move_time_millis = millis();
      }
  }

}

#endif
