#include <Stepper.h>
class Dto {
    public:
        boolean shortest; //TODO
        int direction;
        boolean lap;
        int pos[12];
};


class CustomStepper{
    private:
        int currentPos = 0;
        int targetPos = 0;
        int direction = 1;
        int lap = 0;
        int pins[4];
        boolean doneMoving;
        Stepper * stepper;  

    public:
    
       CustomStepper(int steps, int a, int b, int c, int d){
           stepper =  new Stepper(steps, a, b, c, d);
           pins[0]=a;pins[1]=b;pins[2]=c;pins[3]=d; 
       };


      void setTarget(int target, boolean lap, boolean shortest, int direction) {
           Serial.print("SetTarget\n Input\ntarget: ");
           Serial.println(target);
           Serial.print("shortest:");
           Serial.println(shortest);
           Serial.print("directiont: ");
           Serial.println(direction);
           Serial.print("lap: ");
           Serial.println(lap);
           Serial.print("\n internal-\ntargetPos:");
           Serial.println(targetPos);
           Serial.print("currentPos: ");
           Serial.println(currentPos);
           Serial.println("\n");
           
    
          if (lap) {
              if((target<=currentPos && direction == 1) || (target>currentPos && direction == -1)){//se tivermos a fretne temos de dar a volta
                  lap=1;
              }
          }
          
          if (shortest){
              //calculate shortest direction          //TODO
          }
          if(target == currentPos && lap == 0) {
            Serial.println("SamePos,lap+ anyway");
            this->lap+=1;
          }
          direction=direction;
          targetPos=target;
          doneMoving= false; 
      }


      void setRPM (int RPM) {
          stepper->setSpeed(RPM);
      }



      boolean move() {
           Serial.print("\n\nStarting Move \nCurrentPos: ");
           Serial.println(currentPos);
           Serial.print("targetPos:");
           Serial.println(targetPos);
           Serial.print("directiont: ");
           Serial.println(direction);
           Serial.print("lap: ");
           Serial.println(lap); 
           Serial.print("-------------\n");
        
           if(doneMoving) {
                Serial.println("Done Moving...");
                return false;
            }
          
           if (currentPos == lap && direction == 1)  {       //lap situation (when its at the top)
                if (lap>0) {
                    Serial.println("Lap-- case 1...");
                    lap--;
               }

                
                currentPos = 0;                              //reset position
           }
           else if (currentPos == 0 && direction == -1)  {  //lap situation (when its at the top)
                Serial.println("Lap-- case 2...");                
                lap--;
                currentPos = lap;                           //reset position
           }
           if (currentPos != targetPos || lap > 0){         //if not already in target move one step
              Serial.println("Move 1 step...");
              stepper->step(direction);
              currentPos+=direction;
          }
          
          if (currentPos == targetPos && lap == 0) {
              Serial.println("Last Step...");              
              doneMoving = true;
              return true;
          }
          delay(5000);
          return false;
                   
      }
};

const int stepsPerRev = 2048; // change this to fit the number of steps per revolution
const int lap = 4096;
const int qlap = 1024;

const int RPM = 15;           // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int nrOfSteppers = 2;

boolean listeningMode = true;
boolean waitingMode = false;

static int steppersDone = 0;

CustomStepper * stepperList[nrOfSteppers];

//1 2 
//3 4
//5 6
void intializeMotors() {
    int stepPos[nrOfSteppers][4] = {{14,15,16,17} , {22,24,26,28}};

    for (int i = 0; i < nrOfSteppers; i++) {
        stepperList[i] = new CustomStepper(RPM,stepPos[i][0],stepPos[i][1],stepPos[i][2],stepPos[i][3]);
        stepperList[i]->setRPM(RPM);
    }   
}

void draw (Dto dto) {
    for (int i = 0; i < nrOfSteppers; i++) {
        stepperList[i]->setTarget(dto.pos[i], dto.lap, dto.shortest, dto.direction);
    }
  }

void setup(){
    Serial.begin(9600);
    
    intializeMotors();

    delay(2000);
    Serial.println("Exiting setup");
}


void loop() {
     Serial.println("\n\n#############################################################################\n");
     Serial.println("                         Starting loop Iteration...");
     Serial.println("\n#############################################################################\n");
     while (listeningMode){
        //ouvir
        delay(1000);
        Serial.println("Received a DTO...");
        Dto dto;
        dto.pos[0]= 3;
        dto.pos[1]= 4;
        dto.lap=0;
        dto.shortest=false;
        dto.direction=1;
        
        Serial.println("Drawing...");
       Serial.println("\n##########################");
       Serial.println("Starting drawing...");
       Serial.println("###########################\n");
        draw(dto);
        listeningMode = false;
        waitingMode = true;
    }

    while(waitingMode) {
        Serial.println("\n##########################");
        Serial.println("Starting waiting...");
        Serial.println("###########################\n");
        //wait for trigger wire
        delay(5000);
        Serial.println("Moving...");
        waitingMode = false;
   }
    
    while (steppersDone < nrOfSteppers){
       Serial.println("\n##########################");
       Serial.println("Starting move Iteration...");
       Serial.println("###########################\n");
       for (int i = 0; i < nrOfSteppers; i++) {
            if(stepperList[i]->move()){
                steppersDone++;
            }
        }
    }        
     Serial.println("Ending Iteration...");
     Serial.println("\n########################################################\n");
    steppersDone = 0;
    listeningMode = true;
}
