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


#include <IRremote.h>



const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup(){
  Serial.begin(9600);

  irrecv.enableIRIn(); 
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
        results.value = key_value;

        Serial.print("loop\n");
        switch(results.value){
          case 0xFF30CF:          
          Serial.print("1");
          break;
          case 0xFF18E7:
          Serial.print("2");
          break;               
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}


