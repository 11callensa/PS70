#include <AccelStepper.h>

const int stepPin = D0; 
const int dirPin = D1;   

// Define a stepper and the pins it will use
AccelStepper stepper(1, stepPin, dirPin); // initialise accelstepper for a two wire board

void setup()
{
}

void loop()
{
  if (stepper.distanceToGo() == 0)
  {
    // Random change to speed, position and acceleration
    // Make sure we dont get 0 speed or accelerations
    delay(1000);
    stepper.moveTo(rand() % 1000);
    stepper.setMaxSpeed((rand() % 1000) + 1);
    stepper.setAcceleration((rand() % 1000) + 1);
  }
  stepper.run();
}