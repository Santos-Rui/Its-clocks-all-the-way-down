#include <Stepper.h>
#include <CustomStepper.h>
#include <Arduino.h>


CustomStepper::CustomStepper(int steps, int a, int b, int c, int d){
    stepper =  new Stepper(steps, a, c, b, d);
    pins[0]=a;pins[2]=b;pins[1]=c;pins[3]=d; 
};


void CustomStepper::setTarget(int target, bool lap, bool shortest, int direction) {
    //Serial.print("SetTarget\n Input\ntarget: ");
    //Serial.println(target);
    //Serial.print("shortest:");
    //Serial.println(shortest);
    //Serial.print("directiont: ");
    //Serial.println(direction);
    //Serial.print("lap: ");
    //Serial.println(lap);
    //Serial.print("\n internal-\ntargetPos:");
    //Serial.println(targetPos);
    //Serial.print("currentPos: ");
    //Serial.println(currentPos);
    //Serial.println("\n");
  
    if (lap) {
        if((target<=currentPos && direction == 1) || (target>currentPos && direction == -1)){//se tivermos a fretne temos de dar a volta
            lap=1;
        }
    }

   if(target == currentPos && lap == 0) {
       //Serial.println("SamePos,lap+ anyway");
       this->lap=1;
   }

    if (shortest){
        //calculate shortest direction          //TODO
    }
    else {
      direction=direction;
    }

    targetPos=target;
    doneMoving=false; 
}


void CustomStepper::setRPM (int RPM) {
    stepper->setSpeed(RPM);
}


bool CustomStepper::move() {
    //Serial.print("current pos  "); Serial.println(currentPos);
    //Serial.print("targetPos pos  "); Serial.println(targetPos);
    if(doneMoving) {
        return false;
    }

    if  (currentPos == 2048){                            
        lap--;    
        currentPos = 0;                                  
    }
    if (currentPos != targetPos || lap > 0){        
        //stepper->step(1);
        currentPos++;
        return false;                            
    }

    if (currentPos == targetPos && lap == 0){
        Serial.println("Last Step...");              
        doneMoving = true;
        return true;
    }
   return false;

 // if(doneMoving) {
 //     //Serial.println("Done Moving...");
 //     return false;
 // }
 //
 // if (currentPos == lap && direction == 1 && lap>0){   //lap situation (when its at the top){
 //     Serial.println("Lap-- case 1...");
 //     lap--;    
 //     currentPos = 0;                                  //reset position
 // }
 // else if (currentPos == 0 && direction == -1){        //lap situation (when its at the top)
 //     Serial.println("Lap-- case 2...");                
 //     lap--;
 //     currentPos = lap;                                //reset position
 // }
 // if (currentPos != targetPos || lap > 0){             //if not already in target move one step
 //     //Serial.println("Move 1 step...");
 //     stepper->step(direction);
 //     currentPos+=direction;
 // }
 //
 //if (currentPos == targetPos && lap == 0){
 //     Serial.println("Last Step...");              
 //     doneMoving = true;
 //     return true;
 //}
   //delay(5000);
   //return false;         
}