//     LCD PARA DEBUG, COMANDO IR E STEPPER

#include <Stepper.h>
#include <LiquidCrystal.h>
#include <IRremote.h>


// LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// IR
int RECV_PIN = 53;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;


// STEPPER
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 12;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm


//1 2 
//3 4
//5 6

Stepper myStepper1m(stepsPerRevolution, 31 , 35 , 33 , 37 );
Stepper myStepper1h(stepsPerRevolution, 30 , 34 , 32 , 36 );

Stepper myStepper2m(stepsPerRevolution, 22 , 26 , 24 , 28 );
Stepper myStepper2h(stepsPerRevolution, 39 , 43 , 41 , 45 );

Stepper myStepper3h(stepsPerRevolution, 23 , 27 , 25 , 29 );
Stepper myStepper3m(stepsPerRevolution, A0, A2, A1, A3 );

Stepper myStepper4m(stepsPerRevolution, A12, A14, A13, A15 );
Stepper myStepper4h(stepsPerRevolution, 38 , 42 , 40  , 44 );

Stepper myStepper5m(stepsPerRevolution,47 , 51 , 49  , 53 );
Stepper myStepper5h(stepsPerRevolution, 46 , 50 , 48  , 52 ); 

Stepper myStepper6m(stepsPerRevolution, A8, A10, A9, A11 );
Stepper myStepper6h(stepsPerRevolution, A4, A6, A5, A7 );




void setup()
{
  myStepper1m.setSpeed(rolePerMinute);
myStepper1h.setSpeed(rolePerMinute);

myStepper2m.setSpeed(rolePerMinute);
myStepper2h.setSpeed(rolePerMinute);

myStepper3h.setSpeed(rolePerMinute);
myStepper3m.setSpeed(rolePerMinute);

myStepper4m.setSpeed(rolePerMinute);
myStepper4h.setSpeed(rolePerMinute);



myStepper5m.setSpeed(rolePerMinute);
myStepper5h.setSpeed(rolePerMinute);

myStepper6m.setSpeed(rolePerMinute);
myStepper6h.setSpeed(rolePerMinute);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);

  lcd.print("    STARTING   "); 
  delay(700);

}




void loop() {
    delay(5000);

  myStepper1m.step(stepsPerRevolution/2);

  
  
  delay(5000);
}