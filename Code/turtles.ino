//  code for the V3 clock

#include <Stepper.h>

const int stepsPerRev = 2038; // change this to fit the number of steps per revolution
const int RPM = 15;           // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int lap = 4076;
const int nrMotors = 12;


typedef struct smotor {
  int currentPos = 0;
  int targetPos = 0;
  int lap = 0;
  int pins[4];
  Stepper * stepper;

  smotor(int a, int b, int c, int d){
      stepper = new Stepper(stepsPerRev, a , c , b , d);
      pins[0]=a;pins[1]=b;pins[2]=c;pins[3]=d;
      currentPos=targetPos=lap=0;
  }

  void setTarget(int target) {
      if(target>=currentPos){lap=1;}  //se tivermos a fretne temos de dar a volta
      targetPos = target;
  }

  void step() {
      if (currentPos==lap){
          currentPos=0;
          lap--;
      }
      if (lap > 0 || currentPos < targetPos){
          stepper->step(1);
          currentPos++;
      } 
  }
}*motor;

//1 2 
//3 4
//5 6
motor listaMotors[nrMotors];

void createMotor() {
  listaMotors[0] = new struct smotor( 14  , 15 ,  16, 17 );  //1 top       
  listaMotors[1] = new struct smotor( 22 ,  24  ,26 , 28 );  //1 bottom   
  
  listaMotors[2] = new struct smotor( 2  ,  3  , 4  ,  5 );  //2 top         
  listaMotors[3] = new struct smotor( 6 ,   7  ,  8 ,  9 );  //2 bottom     
  
  listaMotors[4] = new struct smotor( 23 ,  25 , 27 , 29 );  //3 top       
  listaMotors[5] = new struct smotor( 38 ,  40  ,42 , 44 );  //3 bottom
  
  listaMotors[6] = new struct smotor( 10 ,  11 , 12 , 13 );  //4 top           
  listaMotors[7] = new struct smotor( 46 , 48  , 50 , 52 );  //4 bottom  
  
  listaMotors[8] = new struct smotor( A0,  A1 ,  A2,  A3 );  //5 top    
  listaMotors[9] = new struct smotor( A4,  A5 ,  A6 , A7 );  //5 bottom 
  
  listaMotors[10] = new struct smotor( A8,  A9 , A10, A11 );  //6 top        
  listaMotors[11] = new struct smotor( A12,  A13, A14, A15);  //6 bottom     
}


void motorSetup() {
  for (int i = 0; i < nrMotors; i++) {
    listaMotors[i]->stepper->setSpeed(RPM);
  }
}


void turnOffAll(){
  for (int i = 0; i < nrMotors; i++) {
        digitalWrite(listaMotors[i]->pins[0], LOW);
        digitalWrite(listaMotors[i]->pins[1], LOW);
        digitalWrite(listaMotors[i]->pins[2], LOW);
        digitalWrite(listaMotors[i]->pins[3], LOW);
    }
}


void moveAll(){
    for (int i = 0; i < nrMotors; i++) {
        listaMotors[i]->step();
    }
}


void setup(){
    createMotor();
    motorSetup();
    for(int a=0;a<1;a++){
        listaMotors[a]->setTarget(lap/2);
    }
    delay(2000);
}


void loop() {
    moveAll();
}


