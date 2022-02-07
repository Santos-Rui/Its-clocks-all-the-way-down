//     LCD PARA DEBUG, COMANDO IR E STEPPER

#include <Stepper.h>

// STEPPER
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 17;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

Stepper myStepper1(stepsPerRevolution, 31, 35, 33, 37);
Stepper myStepper2(stepsPerRevolution, 30, 34, 32, 36);


void setup()
{
  myStepper1.setSpeed(rolePerMinute);
  myStepper2.setSpeed(rolePerMinute);

}




void loop() {
  myStepper1.step(stepsPerRevolution*2);
  myStepper2.step(stepsPerRevolution*2);

  delay(2000);
}
