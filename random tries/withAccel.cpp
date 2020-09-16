//     LCD PARA DEBUG, COMANDO IR E STEPPER

#include <AccelStepper.h>
#include <LiquidCrystal.h>
#include <IRremote.h>


#define FULLSTEP 4
#define HALFSTEP 8

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

AccelStepper myStepper1(HALFSTEP, 41, 45, 43, 47);
AccelStepper myStepper2(HALFSTEP, 40, 44, 42, 46);
AccelStepper myStepper3(HALFSTEP, 31, 35, 33, 37);
AccelStepper myStepper4(HALFSTEP, 30, 34, 32, 36);


void setup()
{

  myStepper1.setMaxSpeed(1000.0);
  myStepper1.setAcceleration(50.0);
  myStepper1.setSpeed(1000);
  myStepper1.moveTo(2048);  // 1 revolution 




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
    myStepper1.runSpeed();
}
