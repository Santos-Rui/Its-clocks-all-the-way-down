
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#include <IRremote.h>

int RECV_PIN = 53;

IRrecv irrecv(RECV_PIN);

decode_results results;


#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);



void setup()
{
    myStepper.setSpeed(rolePerMinute);

  lcd.begin(16, 2);
  lcd.print("o nelo foi beta"); 
  lcd.setCursor(0, 1);
  lcd.print("    vezes hoje "); 
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {

  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
    if (irrecv.decode(&results)) {
      lcd.setCursor(0, 1);
      lcd.print(results.value, HEX);
      irrecv.resume(); // Receive the next value
      Serial.println("clockwise");
      myStepper.step(stepsPerRevolution);
      delay(500);
  }
  delay(1000);
}