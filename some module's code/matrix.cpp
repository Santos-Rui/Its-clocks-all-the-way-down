#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 23 is connected to the DataIn 
 pin 25 is connected to LOAD(CS)
 pin 27 is connected to the CLK 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(23,27,25,1);

/* image switching time */
unsigned long delaytime1=500;
unsigned long delaytime2=50;

byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
  byte A[] = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
  byte B[] = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
  byte C[] = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
  byte D[] = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
  byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
  byte F[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
  byte G[] = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
  byte H[] = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
  byte I[] = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
  byte J[] = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
  byte K[] = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
  byte L[] = {B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000};
  byte M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
  byte N[] = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
  byte O[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
  byte P[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
  byte Q[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
  byte R[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
  byte S[] = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
  byte T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
  byte U[] = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
  byte V[] = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
  byte W[] = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
  byte X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
  byte Y[] = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
  byte Z[] = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000};

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
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
  case 'G':
  case 'g':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, G[i]);
    }
    break;
  case 'h':
  case 'H':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, H[i]);
    }
    break;
  case 'I':
  case 'i':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, I[i]);
    }
    break;
  case 'L':
  case 'l':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, L[i]);
    }
    break;    
  case 'O':
  case 'o':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, O[i]);
    }
    break;
  case 'S':
  case 's':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, S[i]);
    }
    break;
  case 'U':
  case 'u':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, U[i]);
    }
    break;
  case 'Y':
  case 'y':
    for(int i=0;i<8;i++){
      lc.setRow(0, i, Y[i]);
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


void writePalavra(String palavra) {

  for (char const &c: palavra) {
        writeLetra(c);
        delay(delaytime1);
  }
  delay(1000);
}

void liga1(int x, int y){
  lc.setLed(0,x,y,1);
}

void desliga1(int x, int y){
  lc.setLed(0,x,y,0);
}

void liga1a1(){
  for(int x=0;x<8;x++){
    for(int y=0;y<8;y++){
      liga1(x,y);
      delay(100);
      }
  }
}

void desliga1a1(){
  for(int x=0;x<8;x++){
    for(int y=0;y<8;y++){
      desliga1(x,y);
      delay(100);
      }
  }
}



void loop() { 
  
writePalavra("O GUILHAS E GAY");

}