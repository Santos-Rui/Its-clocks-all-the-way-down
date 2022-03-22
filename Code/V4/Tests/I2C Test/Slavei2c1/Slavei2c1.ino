#include <Stepper.h>
#include <Wire.h>                               

class Dto {
    public:
        boolean shortest; //TODO
        int direction;
        boolean lap;
        int pos[12];
};

void receiveEvent(int howMany)

{
    Serial.println("receved event");

  while(1 < Wire.available()) // loop through all but the last

  {

    char c = Wire.read(); // receive byte as a character

    Serial.print(c);         // print the character

  }

  int x = Wire.read();    // receive byte as an integer

  Serial.println(x);         // print the integer

}


void setup(){
    Serial.begin(9600);
    Serial.println("Starting setup");
    Wire.begin(1);                                
    delay(2000);
    Wire.onReceive(receiveEvent); // register event
    Serial.println("Exiting setup");
}

int available = 0;

void loop() {                                   
}
