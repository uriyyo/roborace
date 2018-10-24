#include "car.h"
#include "controller.h"
#include "rangefinder.h"

#define FORWARD_PIN 5
#define BACKWARD_PIN 6
#define SERVO_PIN 3

#define FORWARD_SENSOR 19 //A5
#define RIGHT_SENSOR A4 //A3
#define LEFT_SENSOR_ECHO 11 
#define LEFT_SENSOR_TRIGGER 8


Controller* contoller;

void setup() {
  Car car (FORWARD_PIN, BACKWARD_PIN, SERVO_PIN);
  car.CancelTurn();

  contoller = new Controller(new RangefinderAnalog(FORWARD_SENSOR),
                             new RangefinderDigital(LEFT_SENSOR_ECHO, LEFT_SENSOR_TRIGGER),
                             new RangefinderAnalog(RIGHT_SENSOR),
                             &car);
  Serial.begin(9600);
}

void loop() {
  contoller->move();
}
