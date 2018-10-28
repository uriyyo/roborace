#include "car.h"
#include "controller.h"
#include "rangefinder.h"

#define FORWARD_PIN 2
#define BACKWARD_PIN 4
#define SPEED_PIN 5
#define SERVO_PIN 3

#define FORWARD_SENSOR 19
#define RIGHT_SENSOR A4
#define LEFT_SENSOR_ECHO 11
#define LEFT_SENSOR_TRIGGER 8

#define BUTTON_PIN 13


Controller *controller;

bool isWorking = false;

void setup() {
    Car car(FORWARD_PIN, BACKWARD_PIN, SERVO_PIN, SPEED_PIN);

    controller = new Controller(new RangefinderDigital(9, 8),
                                new RangefinderDigital(11, 12),
                                new RangefinderDigital(6, 7),
                                &car);

    car.CancelTurn();
    pinMode(BUTTON_PIN, INPUT_PULLUP);

#ifdef DEBUG
    Serial.begin(9600);
#endif
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);
    if (buttonState == LOW) {
        isWorking = !isWorking;
        delay(1000);
    }

    if (isWorking) {
        controller->move();
    } else {
        controller->stop();
    }
    
#ifdef DEBUG
    controller->logStates();
#endif
}
