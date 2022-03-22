#include <Dto.h>
#include <CustomStepper.h>  
#include <Stepper.h>
#include <Wire.h>                               

//number of the slave
const int slaveNr = 1; //hours number 1 (left)


//pin to trigger movement
int triggerPin = 23;    // pushbutton connected to digital pin 7


//stepper settings
const int stepsPerRev = 2048; //steps per revolution
const int RPM = 15;           // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int nrOfSteppers = 12;


//control vars
boolean listeningMode = true;
boolean waitingMode = true;
static int steppersDone = 0;


//"buffers"
int val = 0;      // variable to store the read value
String buffer = "";


//Stepper positions
int stepPos[nrOfSteppers][4] = {
      {22,24,26,28},  {2 ,3, 4 ,5 }       ,    {10,11,12,13} ,  {6, 7, 8, 9},     // 1.1-1.2      2.1-2.2      1 2 
      {A4,A5,A6,A7},{A12,A13,A14,A15}     ,    {A0,A1,A2,A3} , {A8,A9,A10,A11},   // 3.1-3.2      4.1-4.2      3 4
      {47,49,51,53} , {39,41,43,45}       ,    {38,40,42,44} ,  {46,48,50,52}     // 5.1-5.2      6.1-6.2      5 6
};


//main struct
CustomStepper * stepperList[nrOfSteppers];


//intializes steppers with pins and rpm
void intializeMotors() {
    for (int i = 0; i < nrOfSteppers; i++) {
        stepperList[i] = new CustomStepper(RPM,stepPos[i][0],stepPos[i][1],stepPos[i][2],stepPos[i][3]);
        stepperList[i]->setRPM(RPM);
    }   
}


//maps the received dto to the global struct
void mapDtoToStruct (Dto dto) {
    for (int i = 0; i < nrOfSteppers; i++) {
        stepperList[i]->setTarget(dto.getData(i), dto.getLap(), dto.getShortest(), dto.getDirection());
    }
  }


//handles i2c recevive event
//reads byte by byte and writes it to a string untill the last char '}'
void receiveEvent(int size){
    Serial.println("\nreceved event");
    int i=0;
    while(0<Wire.available()){    
        char c = Wire.read();
        buffer = buffer + c;
        if(c=='}'){
            Serial.println("Full string");
            Serial.println(buffer);
            listeningMode = false;
            break;
        }
    }
}


void setup(){
    Serial.println("Starting Setup");
    Serial.begin(9600);

    //Join i2c as a slave                           
    Wire.begin(slaveNr);
            
    //register the receiver                        
    Wire.onReceive(receiveEvent);

    //Steppers
    intializeMotors();

    Serial.println("Exiting setup");
}


void loop() {
    Serial.println("Starting loop Iteration...");    
    Serial.println("Starting waiting for data...");
    
    while (listeningMode){
        delay(25);
    }
      
    Serial.println("Received data, creating dto...");
    Dto dto;
    dto.setDto(buffer);
    
    Serial.println("Mapping dto...");
    mapDtoToStruct(dto);

    //Clear buffer
    buffer = "";

    //Wait for the trigger to actually start moving
    Serial.println("Starting waiting for trigger wire...");
    while(waitingMode) {
        val = digitalRead(triggerPin); // read the input pin
        Serial.print("val = "); Serial.println(val);
        if (val == HIGH) {
              waitingMode = false;
        }
        delay(20);
    }

    //move untill every stepper is done
    Serial.println("Moving...");
    while (steppersDone != 12){
        for (int i = 0; i < 12; i++) {
            //Serial.print("moving stepper "); Serial.println(i);
            boolean lastStep = stepperList[i]->move();
            if(lastStep){
                steppersDone++;
                Serial.print("Sppers done "); Serial.println(steppersDone);
            }
        }
    }     
 
    steppersDone = 0;
    listeningMode = true;
    waitingMode = true;
    Serial.println("Ending Iteration...\n\n"); 
}
