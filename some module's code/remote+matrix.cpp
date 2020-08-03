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

byte A[] = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
byte B[] = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};

#include "LedControl.h"
LedControl lc=LedControl(23,27,25,1);

#include <IRremote.h>


const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  irrecv.blink13(true);
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop(){
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
        results.value = key_value;

        
        switch(results.value){
          case 0xFF30CF:          
          writeLetra('a');
          break;
          case 0xFF18E7:
          writeLetra('e');
          break;               
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}


void writeLetra(char c){ //tem que haver uma maneira melhor de fazer esta bosta

  switch(c){
  case ' ':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, 0);
    }
    break;
  case 'A':
  case 'a':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, A[i]);
    }
    break; 
  case 'E':
  case 'e':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, E[i]);
    }
    break;
  }



 
  
}

void clean(){  
  lc.setRow(0,0,0);
  lc.setRow(0,1,0);
  lc.setRow(0,2,0);
  lc.setRow(0,3,0);
  lc.setRow(0,4,0);
  lc.setRow(0,5,0);
  lc.setRow(0,6,0);
  lc.setRow(0,7,0);
}
