#include <Stepper.h>
#include <Wire.h>                               
#include <Dto.h>


String s = "";

char buffer[128];
bool reading = true;
void receiveEvent(int howMany){
  
  Serial.println("\nreceved event");
  int i=0;
  while(0<Wire.available()){
    
    char c = Wire.read();
    s = s + c;
    if(c=='}'){
      Serial.println("Full string");
      Serial.println(s);
      }
  }

}


void setup(){
    Serial.begin(9600);
    Serial.println("Starting setup");
    Wire.begin(2);                                
    delay(2000);
    Wire.onReceive(receiveEvent); // register event
    Serial.println("Exiting setup");
}

int available = 0;

void loop() {                                                    
}
