#include "car.h"

#define FORWARD_MOVE 1
#define BACKWARD_MOVE 0
#define LEFT_TURN 1
#define RIGHT_TURN 0

Car::Car(int ForwardPin, int BackwardPin, int RightPin, int LeftPin)
{
    this->ForwardPin  = ForwardPin;
    this->BackwardPin = BackwardPin;
    this->LeftPin     = LeftPin;
    this->RightPin    = RightPin;

    pinMode(ForwardPin , OUTPUT);
    pinMode(BackwardPin, OUTPUT);
    pinMode(LeftPin    , OUTPUT);
    pinMode(RightPin   , OUTPUT);
}

void DoTurn(int Turn)
{
    if (Turn == LEFT_TURN)
    {
        digitalWrite(RightPin, LOW);
        digitalWrite(LeftPin , HIGH);
    }
    else if (Turn == RIGHT_TURN)
    {
        digitalWrite(LeftPin, LOW);
        digitalWrite(RightPin , HIGH);
    }
}

void DoMove(int Move)
{
    if (Move == FORWARD_MOVE)
    {
        digitalWrite(BackwardPin, LOW);
        digitalWrite(ForwardPin , HIGH);
    }
    else if (Move == BACKWARD_MOVE)
    {
        digitalWrite(ForwardPin  , LOW);
        digitalWrite(BackwardPin , HIGH);
    }
}

void Stop()
{
    digitalWrite(BackwardPin, LOW);
    digitalWrite(ForwardPin , LOW);
}

void CancelTurn()
{
    digitalWrite(LeftPin  , LOW);
    digitalWrite(RightPin , LOW);
}

void Car::Forward(int milliseconds = -1)
{
    DoMove(FORWARD_MOVE);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(Stop);
    */
}

void Car::Backward(int milliseconds = -1)
{
    DoMove(BACKWARD_MOVE);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(Stop);
    */
}

void Car::Left(int milliseconds = -1)
{
    DoTurn(LEFT_TURN);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(CancelTurn);
    */
}

void Car::Right(int milliseconds = -1)
{
    DoTurn(RIGHT_TURN);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(CancelTurn);
    */
}