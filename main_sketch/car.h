#ifndef Car_h
#define Car_h
 
//#include "WProgram.h"
 
class Car
{
    public:
        Car(int ForwardPin, int BackwardPin, int RightPin, int LeftPin);

        //milliseconds - in future will be possible to run some command during some specific time
        //when milliseconds time expire - it undo commands 
        //(Forward and Backward go to Stop() ; Left and Right go to CancelTurn())
        void Forward (int milliseconds = -1);
        void Backward(int milliseconds = -1);
        void Left    (int milliseconds = -1);
        void Right   (int milliseconds = -1);

        //sets ForwardPin and BackwardPin to LOW
        void Stop();
        //sets LeftPin and RightPin to LOW
        void CancelTurn();
    private:
        int ForwardPin;
        int BackwardPin;
        int LeftPin;
        int RightPin;

        //only this functions sets HIGH value on pins!!!!
        //For exclusion setting of HIGH on Left and Right pins in the same time
        void DoTurn(int Turn);
        //For exclusion setting of HIGH on Forward and Backward pins in the same time
        void DoMove(int Move);

};


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

void Car::DoTurn(int Turn)
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

void Car::DoMove(int Move)
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

void Car::Stop()
{
    digitalWrite(BackwardPin, LOW);
    digitalWrite(ForwardPin , LOW);
}

void Car::CancelTurn()
{
    digitalWrite(LeftPin  , LOW);
    digitalWrite(RightPin , LOW);
}

void Car::Forward(int milliseconds )
{
    DoMove(FORWARD_MOVE);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(Stop);
    */
}

void Car::Backward(int milliseconds)
{
    DoMove(BACKWARD_MOVE);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(Stop);
    */
}

void Car::Left(int milliseconds )
{
    DoTurn(LEFT_TURN);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(CancelTurn);
    */
}

void Car::Right(int milliseconds )
{
    DoTurn(RIGHT_TURN);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(CancelTurn);
    */
}


#endif
