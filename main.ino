#include "Car/car.h"
#include "Rangefinder/rangefinder.h"
#include "controller.h"

Controller* controller;

void setup() {
  Rangefinder* right = new Rangefinder(13, 11);
  Rangefinder* left = new Rangefinder(12, 10);
  Rangefinder* front = new Rangefinder(7, 6);

  controller = new Controller(front, left, right);

  Serial.begin(9600);
}

void loop() {
  controller->move();
  delay(100);
}
