#ifndef Car_h
#define Car_h

#include <Servo.h>

#define MAX_LEFT_ANGLE 80
#define MAX_RIGHT_ANGLE 180
#define MIDDLE_ANGLE 127


class Car
{
    public:
        Car(){};
        Car(int ForwardPin, int BackwardPin, int ServoPin);

        //milliseconds - in future will be possible to run some command during some specific time
        //when milliseconds time expire - it undo commands 
        //(Forward and Backward go to Stop() ; Left and Right go to CancelTurn())
        void Forward ();
        void Backward();
        void Left    (int percent = -1);
        void Right   (int percent = -1);
        
        //sets ForwardPin and BackwardPin to LOW
        void Stop();
        //sets LeftPin and RightPin to LOW
        void CancelTurn();
    private:
        int ForwardPin;
        int BackwardPin;
        Servo ServoTurn;

        //only this functions sets HIGH value on pins!!!!
        //For exclusion setting of HIGH on Forward and Backward pins in the same time
        void DoMove(int Move);

        void DoTurn(int Turn);
};


#define FORWARD_MOVE 1
#define BACKWARD_MOVE 0
#define LEFT_TURN -100
#define RIGHT_TURN -200

Car::Car(int ForwardPin, int BackwardPin, int ServoPin)
{
    this->ForwardPin  = ForwardPin;
    this->BackwardPin = BackwardPin;
    this->ServoTurn.attach(ServoPin);

    pinMode(ForwardPin , OUTPUT);
    pinMode(BackwardPin, OUTPUT);
}

void Car::DoTurn(int Turn)
{
    if (Turn == LEFT_TURN)
    {
        ServoTurn.write(MAX_LEFT_ANGLE);
    }
    else if (Turn == RIGHT_TURN)
    {
        ServoTurn.write(MAX_RIGHT_ANGLE);
    }
    else if (Turn >=0 && Turn <= 180)
    {     
        ServoTurn.write(Turn);
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
    ServoTurn.write( MIDDLE_ANGLE);
}

void Car::Forward()
{
    DoMove(FORWARD_MOVE);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(Stop);
    */
}

void Car::Backward()
{
    DoMove(BACKWARD_MOVE);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(Stop);
    */
}

void Car::Left(int percent)
{
    if (percent == -1)
    {
        DoTurn(LEFT_TURN);
        return;
    }

    int angle = MAX_LEFT_ANGLE + 
        (MIDDLE_ANGLE-MAX_LEFT_ANGLE)*percent / 100;
    DoTurn(angle);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(CancelTurn);
    */
}

void Car::Right(int percent)
{
    if (percent == -1)
    {
        DoTurn(RIGHT_TURN);
        return;
    }

    int angle = MIDDLE_ANGLE + 
        (MAX_RIGHT_ANGLE-MIDDLE_ANGLE)*percent / 100;
    DoTurn(angle);
    /* XXX TODO: add timers
    if ( milliseconds != -1)
        addTimer(CancelTurn);
    */
}


#endif
