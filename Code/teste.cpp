//     LCD PARA DEBUG, COMANDO IR E STEPPER

#include <Stepper.h>
#include <LiquidCrystal.h>
#include <IRremote.h>



// STEPPER
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

Stepper myStepper1(stepsPerRevolution, 14, 16, 15, 17);




void setup()
{
  myStepper1.setSpeed(rolePerMinute);


  delay(700);
}




void loop() {
  myStepper1.step(stepsPerRevolution/2);
  delay(2000);
}
