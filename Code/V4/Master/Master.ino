#include <Wire.h>
#include <Dto.h>
#include "DS1307.h"

//clock
DS1307 clock;//define a object of DS1307 class

//pin to trigger movement
int triggerPin = 25;  

//Dtos for 4 clocks hardcoded like a noob
Dto dto1;
Dto dto2;
Dto dto3;
Dto dto4;

// RGB Pins
#define BLUE 33
#define GREEN 35
#define RED 37

//positions for each 1/8 of the circle
                        int TOP = 0;
       int TOP_LEFT = 1792;       int TOP_RIGHT = 256;                             
int LEFT = 1536;                              int RIGHT = 512;
     int BOTTOM_LEFT = 1280;      int BOTTOM_RIGHT = 768;
                    int BOTTOM = 1024;


//How to draw each number + rest position + degrees
int numbers[13][12] = { {  RIGHT  ,  BOTTOM  ,  LEFT  , BOTTOM ,  BOTTOM  ,    TOP   , BOTTOM ,   TOP  ,    TOP   ,   RIGHT  ,  TOP  , LEFT },        //ZERO
                        {TOP_LEFT , TOP_LEFT , BOTTOM , BOTTOM , TOP_LEFT , TOP_LEFT ,   TOP  , BOTTOM , TOP_LEFT , TOP_LEFT ,  TOP  , TOP  },        //ONE
                        {  RIGHT  ,   RIGHT  ,  LEFT  , BOTTOM ,  RIGHT   ,  BOTTOM  ,   TOP  ,  LEFT  ,    TOP   ,   RIGHT  ,  LEFT , LEFT },        //TWO
                        {  RIGHT  ,   RIGHT  ,  LEFT  , BOTTOM ,  RIGHT   ,  BOTTOM  ,   TOP  ,  LEFT  ,    TOP   ,   RIGHT  ,  LEFT , LEFT },        //THREE
                        { BOTTOM  ,  BOTTOM  , BOTTOM , BOTTOM ,   TOP    ,   RIGHT  ,   TOP  , BOTTOM , TOP_LEFT , TOP_LEFT ,  TOP  , TOP  },        //FOUR
                        {  RIGHT  ,  BOTTOM  ,  LEFT  ,  LEFT  ,   TOP    ,   RIGHT  , BOTTOM ,  LEFT  ,   RIGHT  ,   RIGHT  ,  TOP  , LEFT },        //FIVE
                        {  RIGHT  ,  BOTTOM  ,  LEFT  ,  LEFT  ,   TOP    ,  BOTTOM  , BOTTOM ,  LEFT  ,    TOP   ,   RIGHT  ,  LEFT , TOP  },        //SIX
                        {  RIGHT  ,   RIGHT  ,  LEFT  , BOTTOM , TOP_LEFT , TOP_LEFT , BOTTOM ,  TOP   , TOP_LEFT , TOP_LEFT ,  TOP  , TOP  },        //SEVEN
                        {  RIGHT  ,  BOTTOM  , BOTTOM ,  LEFT  ,   TOP    ,   RIGHT  ,   TOP  ,  LEFT  ,    TOP   ,  RIGHT   ,  TOP  , LEFT },        //EIGHT
                        {  RIGHT  ,  BOTTOM  , BOTTOM ,  LEFT  ,   TOP    ,   RIGHT  ,   TOP  , BOTTOM ,   RIGHT  ,  RIGHT   ,  TOP  , LEFT },        //NINE
                        {  LEFT   ,   LEFT   ,  LEFT  ,  LEFT  ,   LEFT   ,   LEFT   ,  LEFT  ,  LEFT  ,   LEFT   ,   LEFT   ,  LEFT , LEFT },        //DEGREES THINGY
                        {  LEFT   ,   LEFT   ,  LEFT  ,  LEFT  ,   LEFT   ,   LEFT   ,  LEFT  ,  LEFT  ,   LEFT   ,   LEFT   ,  LEFT , LEFT },        //C
                        {   TOP   ,    TOP   ,  TOP   ,   TOP  ,   TOP    ,   TOP    ,   TOP  ,  TOP   ,    TOP   ,   TOP    ,  TOP  , TOP  }         //REST                                 
                      };



  
void sendDto(Dto sto, int slave){
    String message = sto.getBytes(); 
    for(int a=0 ; a < message.length()/32 +1 ; a++){
        Wire.beginTransmission(slave);
        Serial.println("\nNewPackage:");
        for(int s=0 ; s<32 && a*32+s<message.length()  ; s++){
            Wire.write(message[a*32+s]);
            delay(25);         
        }
        Wire.endTransmission();    // stop transmitting
    }
}


void drawDtos(){
      int hours = clock.hour;
      int minutes = clock.minute;
      
      int hours1 = hours / 10;  
      int hours2 = hours % 10;
      int minutes1 = minutes / 10; 
      int minutes2 = minutes % 10;     
      
      Serial.print("hours1 : ");  Serial.println(hours1);
      Serial.print("hours2 : ");  Serial.println(hours2);
      Serial.print("minutes1 : ");  Serial.println(minutes1);
      Serial.print("minutes2 : ");  Serial.println(minutes2);

      dto1.setLap(0);
      dto1.setShortest(0);
      dto1.setDirection(0);
      dto1.setData(numbers[hours1]);   

      dto2.setLap(0);
      dto2.setShortest(0);
      dto2.setDirection(0);
      dto2.setData(numbers[hours2]); 
      
      dto3.setLap(0);
      dto3.setShortest(0);
      dto3.setDirection(0);
      dto3.setData(numbers[minutes1]); 

      dto4.setLap(0);
      dto4.setShortest(0);
      dto4.setDirection(0);
      dto4.setData(numbers[minutes2]);         
  }


void setup(){
    Serial.begin(9600);
    Serial.println("Starting setup");
    
    pinMode(RED, OUTPUT); pinMode(GREEN, OUTPUT); pinMode(BLUE, OUTPUT);
    digitalWrite(RED, HIGH);digitalWrite(GREEN, LOW);digitalWrite(BLUE, HIGH); //white
    
    clock.begin();
    Wire.begin(); // join i2c bus (address optional for master)
    
    digitalWrite(RED, LOW);digitalWrite(GREEN, LOW);digitalWrite(BLUE, LOW); //OFF
    Serial.println("Exiting setup");
    digitalWrite(triggerPin, LOW);

}


void loop() {
    clock.getTime();
    int seconds = clock.second;
    Serial.println(clock.second, DEC); 

    if(seconds > 30){
        seconds = seconds - 30;
      }
    Serial.println(seconds); 

    if(seconds < 10 && seconds != 0) {
      digitalWrite(BLUE, HIGH); //BLUE
      delay(100);
      digitalWrite(BLUE, LOW); //OFF
    }

    else if(seconds == 10) {
        Serial.println("Drawing dtos... ");
        digitalWrite(BLUE, HIGH); //BLUE
        drawDtos();
        delay(3000);
        digitalWrite(BLUE, LOW); //OFF
    }

    else if(seconds < 20) {
        digitalWrite(RED, HIGH); //RED
        delay(100);
        digitalWrite(RED, LOW); //OFF
    }

    else if(seconds == 20) {
        digitalWrite(RED, HIGH); //RED
        Serial.println("Sending dtos... ");     
        sendDto(dto1, 1);
        delay(50);
        //sendDto(dto2, 2);
        delay(50);      
        //sendDto(dto3, 3);
        delay(50);               
        //sendDto(dto4, 4);
        delay(50);
        digitalWrite(RED, LOW); //OFF
    }

    else if(seconds < 30) {
        digitalWrite(RED, HIGH); digitalWrite(BLUE, HIGH); //Purple? green is broken...
        delay(100);
        digitalWrite(RED, LOW); digitalWrite(BLUE, LOW); //OFF
    }

    if(seconds == 30 || seconds == 0) {
        digitalWrite(RED, HIGH) ;digitalWrite(BLUE, HIGH); //Purple? green is broken...
        Serial.println("Sending trigger...");
        
        Wire.beginTransmission(1);
        Wire.write('!');
        Wire.endTransmission();    // stop transmitting
        
        digitalWrite(RED, LOW) ;digitalWrite(BLUE, LOW); //OFF
    }     
    delay(700);
}
