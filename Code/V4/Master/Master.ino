#include <Wire.h>
#include <Stepper.h>

class Dto {
    public:
        boolean shortest; //TODO
        int direction;
        boolean lap;
        int pos[12];
};


void setup(){
    Serial.begin(9600);

    Dto dto; //28 bytes
    dto.direction = 1;
    dto.lap = true;
    dto.pos[0] = 1024;
    dto.pos[1] = 1024;
    dto.pos[2] = 1024;
    dto.pos[3] = 1024;
    dto.pos[4] = 1024;
    Serial.println("size of");
    Serial.println(sizeof(dto));

    Wire.begin(1);    
                                                        
    Serial.println("Waiting 5 seconds to write");
    delay(5000);

    Serial.println("Writing dto to 1");
    Wire.beginTransmission(1);
    Wire.write((uint8_t*)&dto,28);                                                    
    Wire.endTransmission();                                                   
    
    Serial.println("Exiting setup");
}


void loop() {
}
