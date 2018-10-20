#ifndef Car_h
#define Car_h

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
 
#endif
