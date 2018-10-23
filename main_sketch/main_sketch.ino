#include "car.h"
#define FORWARD_PIN 5
#define BACKWARD_PIN 6
#define SERVO_PIN 3

#define LEFT_SENSOR 19 //A5
#define FORWARD_SENSOR 18 //A4
#define RIGHT_SENSOR 17 //A3



Car car;
void setup() {
  // put your setup code here, to run once:
  car = Car(FORWARD_PIN,BACKWARD_PIN,SERVO_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  car.Forward();
}
