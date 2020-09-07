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

Stepper myStepper1(stepsPerRevolution, 41, 45, 43, 47);
Stepper myStepper2(stepsPerRevolution, 40, 44, 42, 46);
Stepper myStepper3(stepsPerRevolution, 31, 35, 33, 37);
Stepper myStepper4(stepsPerRevolution, 30, 34, 32, 36);


void setup()
{
  myStepper1.setSpeed(rolePerMinute);
  myStepper2.setSpeed(rolePerMinute);
  myStepper3.setSpeed(rolePerMinute);
  myStepper4.setSpeed(rolePerMinute);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);

  lcd.print("    STARTING   "); 
  delay(700);
  lcd.clear();
  delay(500);
  lcd.print("    STARTING   "); 
  delay(700);
}




void loop() {
	myStepper1.step(stepsPerRevolution/2);
  myStepper3.step(stepsPerRevolution/2);
 	myStepper4.step(stepsPerRevolution/2);
 	delay(2000);
}
