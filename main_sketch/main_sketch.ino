#include "car.h"
#include "controller.h"
#include "rangefinder.h"

#define FORWARD_PIN 2
#define BACKWARD_PIN 4
#define SPEED_PIN 5
#define SERVO_PIN 3

#define FORWARD_SENSOR 19 //A5
#define RIGHT_SENSOR A4 //A3
#define LEFT_SENSOR_ECHO 11
#define LEFT_SENSOR_TRIGGER 8


Controller* contoller;

RangefinderDigital front(9, 8);
RangefinderDigital left(11, 12);
RangefinderDigital right(6, 7);

void setup() {
  Car car (FORWARD_PIN, BACKWARD_PIN, SERVO_PIN, SPEED_PIN);
  car.CancelTurn();

  contoller = new Controller(new RangefinderDigital(9, 8),
                             new RangefinderDigital(11, 12),
                             new RangefinderDigital(6, 7),
                             &car);

  Serial.begin(9600);
}

void loop() {
  contoller->move();
//    Serial.print("Left: \t");
//    Serial.print(left.getDistance());
//    Serial.print("Right: \t");
//    Serial.print(right.getDistance());
//    Serial.print("Front: \t");
//    Serial.print(front.getDistance());
//    Serial.println();

//  delay(100);
}
