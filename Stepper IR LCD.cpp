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
const int rolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);




void setup()
{
  myStepper.setSpeed(rolePerMinute);

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
  lcd.clear();
  lcd.setCursor(0, 0);
  //lcd.print(millis()/1000);
  lcd.print("  WAITING  FOR");
  lcd.setCursor(0, 1);
  lcd.print("  BUTTON PRESS");
    if (irrecv.decode(&results)) {
    	if (results.value == 0XFFFFFFFF){
        	results.value = key_value;
    	}



      	switch(results.value){
          	case 0xFF30CF:    // 1  
          	case 0x9716BE3F:    
         		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 1 ");
 				myStepper.step(2048);

 				//delay(1000);
         		break;

          	case 0xFF18E7:   // 2
          	case 0x3D9AE3F7:
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 2 ");
 				for(int i =0;i<2048;i++){
 					myStepper.step(1);
 				}

         		break;

          	case 0xFF7A85:   // 3
          	case 0x6182021B:
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 3 ");
 				myStepper.step(512);
         		break;

          	case 0xFF10EF:   // 4
          	case 0x8C22657B:
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 4 ");
 				delay(2000);
         		break;

          	case 0xFF38C7:   // 5
          	case 0x488F3CBB:
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 5 ");
 				delay(2000);
         		break;

          	case 0xFF5AA5:   // 6
          	case 0x449E79F:
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 6 ");
 				delay(2000);
         		break;

          	case 0xFF42BD:   // 7
          	//case 0x
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 7 ");
 				delay(2000);
         		break;

          	case 0xFF4AB5:   // 8
          	case 0xFF1BC01:
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 8 ");
 				delay(2000);
         		break;

         	case 0xFF52AD:   // 9
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 9 ");
 				delay(2000);
         		break;

         	case 0xFF6897:   // 0
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("    BUTTON 0 ");
 				delay(2000);
         		break;







         	case 0xFF906F:   // up    FF906F
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("      UP ");
 				delay(2000);
         		break;
         	case 0xFFE01F:   // down  FFE01F
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("      DOWN ");
 				delay(2000);
         		break;         	
         	case 0xFF22DD:   // left  FF22DD
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("      LEFT ");
 				delay(2000);
         		break;

         	case 0xFFC23D:   // right FFC23D
         	case 0x20FE4DBB:
          		lcd.clear();
 				lcd.setCursor(0, 0);
 				lcd.print("     RIGHT ");
 				delay(2000);
         		break;








         	default:
         	    lcd.clear();
      			lcd.setCursor(4, 0);
      			lcd.print(results.value, HEX);
      			delay(2000);
      			break;
        }



       
      //Serial.println(results.value, HEX);
      key_value = results.value;
      irrecv.resume();// Receive the next value



  }
  delay(250);
}

// power FFA25D
// func  FFE21D
// vol+  FF629D
// vol-  FFA857
// left  FF22DD
// right FFC23D
// pause FF02FD
// up    FF906F
// down  FFE01F
// eq    FF9867
// rept  FFB04F
//  1    FF30CF
//  2    FF18E7
//  3    FF7A85
//  4    FF10EF
//  5    FF38C7 
//  6    FF5AA5
//  7    FF42BD
//  8    FF4AB5
//  9    FF52AD
//  0    FF6897