#ifndef Controller_h
#define Controller_h

#include "rangefinder.h"

#define MAX_FRONT_SPEED 250
#define MIN_FRONT_SPEED 210
#define FRONT_SPEED_RANGE (MAX_FRONT_SPEED - MIN_FRONT_SPEED)

#define TURN_DELAY 25
#define MIN_DELAY 0

#define BACKWARD_SPEED 230
#define BACKWARD_DELAY 400
#define BACKWARD_TIMEOUT 300

#define TURN_START_DISTANCE 50

#define MAX_DISTANCE 100
#define MIN_DISTANCE 10
#define DISTANCE_RANGE (MAX_DISTANCE - MIN_DISTANCE)

#define WALL_COLLISION_DISTANCE 40

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
    FRONT_FROM_BACKWARD,
    BACKWARD,
    MAX_MOVE_STATE
};

int move_delays[MAX_MOVE_STATE] = {
        MIN_DELAY,
        BACKWARD_DELAY,
        BACKWARD_DELAY
};

class Controller {
private:
    Rangefinder *front;
    Rangefinder *left;
    Rangefinder *right;
    Car *car;

    TurnType turn_type;
    MoveType move_type;

    unsigned long last_turn_time_millis;
    unsigned long last_move_time_millis;

    bool partial_turn;

    TurnType getNextStateTurn(long front_distance, long left_distance, long right_distance);

    void setNextStateTurn(long front_distance, long left_distance, long right_distance);

    MoveType getNextStateMove(long front_distance);

    long getCarSpeed(long front_distance);


public:
    Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right, Car *car);

    void move();

    void stop();

    void logStates();

};

Controller::Controller(Rangefinder *front, Rangefinder *left, Rangefinder *right, Car *car) {
    this->front = front;
    this->left = left;
    this->right = right;
    this->car = car;
    this->turn_type = NO_TURN;
    this->move_type = FRONT;
}

void Controller::stop() {
    car->Stop();
    car->CancelTurn();
}

long Controller::getCarSpeed(long front_distance) {
    if (front_distance > MAX_DISTANCE) {
        return MAX_FRONT_SPEED;
    } else if (front_distance < MIN_DISTANCE) {
        return MIN_FRONT_SPEED;
    }

    return MIN_FRONT_SPEED + FRONT_SPEED_RANGE * (((float) (front_distance - MIN_DISTANCE)) / DISTANCE_RANGE);
}

TurnType Controller::getNextStateTurn(long front_distance, long left_distance, long right_distance) {
    if (front_distance < TURN_START_DISTANCE) {
        partial_turn = false;

        if (left_distance < right_distance)
            return RIGHT_TURN;
        else
            return LEFT_TURN;

    } else {
        if (left_distance < WALL_COLLISION_DISTANCE) {
            partial_turn = true;
            return RIGHT_TURN;
        } else if (right_distance < WALL_COLLISION_DISTANCE) {
            partial_turn = true;
            return LEFT_TURN;
        }
    }

    return NO_TURN;
}

void Controller::setNextStateTurn(long front_distance, long left_distance, long right_distance) {
    turn_type = getNextStateTurn(front_distance, left_distance, right_distance);

    if (turn_type != NO_TURN)
        last_turn_time_millis = millis();
    else
        car->CancelTurn();
}

MoveType Controller::getNextStateMove(long front_distance) {
    if (front_distance < MIN_DISTANCE) {
        return BACKWARD;
    } else {
        return FRONT;
    }
}

void Controller::move() {
    long left_distance = left->getDistance();
    long right_distance = right->getDistance();
    long front_distance = front->getDistance();

    if (turn_type == NO_TURN || millis() - last_turn_time_millis > turn_delays[turn_type]) {
        setNextStateTurn(front_distance, left_distance, right_distance);
    } else {
        int turn_degree = 100;

        if (partial_turn || move_type != BACKWARD) {
            float distance_to_wall = WALL_COLLISION_DISTANCE - (
                    turn_type == RIGHT_TURN ? left_distance : right_distance
            );

            if (distance_to_wall > 0) {
                turn_degree = (distance_to_wall / WALL_COLLISION_DISTANCE) * 100;

                if (turn_degree > 40) {
                    turn_degree = 100;
                }
            }
        }

        TurnType temp_turn_type = move_type == BACKWARD
                                  ? (turn_type == LEFT_TURN ? RIGHT_TURN : LEFT_TURN)
                                  : turn_type;

        if (temp_turn_type == LEFT_TURN) {
            // TODO: need to fix car.Left API
            car->Left(100 - turn_degree);
        } else {
            car->Right(turn_degree);
        }
    }

    if (move_type == BACKWARD) {
        if (millis() - last_move_time_millis > move_delays[move_type]) {
            car->Stop();
            delay(BACKWARD_TIMEOUT);

            last_move_time_millis = millis();
            last_turn_time_millis = millis();

            move_type = FRONT;
        } else {
            car->Backward(BACKWARD_SPEED);

            if (getNextStateMove(front_distance) == BACKWARD) {
                last_move_time_millis = millis();
            }
        }
    } else if (move_type == FRONT_FROM_BACKWARD) {
        if (millis() - last_move_time_millis > move_delays[move_type]) {
            move_type = FRONT;
        } else {
            car->Forward(BACKWARD_SPEED);
        }
    } else {
        car->Forward(getCarSpeed(front_distance));
        move_type = getNextStateMove(front_distance);

        if (move_type == BACKWARD) {
            car->Stop();
            delay(BACKWARD_TIMEOUT);

            last_move_time_millis = millis();
        }
    }

}

void Controller::logStates() {
    Serial.print("Left: \t");
    Serial.print(left->getDistance());
    Serial.print("\tRight: \t");
    Serial.print(right->getDistance());
    Serial.print("\tFront: \t");
    Serial.print(front->getDistance());

    Serial.print("\t | turn state - ");

    if (turn_type == LEFT_TURN) {
        Serial.print("LEFT_TURN");
    } else if (turn_type == RIGHT_TURN) {
        Serial.print("RIGHT_TURN");
    } else {
        Serial.print("NO_TURN");
    }

    Serial.print("\t move state - ");

    if (move_type == FRONT) {
        Serial.print("FRONT");
    } else {
        Serial.print("BACKWARD");
    }

    Serial.print("\t car speed - ");
    Serial.print(getCarSpeed(front->getDistance()));
    Serial.println();
}

#endif
