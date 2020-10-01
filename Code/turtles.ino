//  code for the V2 clock

#include <Stepper.h>

const int stepsPerRev = 2048; // change this to fit the number of steps per revolution
const int RPM = 12;           // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int lap = 1024;
const int nrMotors = 1;


struct motor {
  int currentPos;
  int targetPos;
  int pins[4];
  Stepper stepper =  Stepper(stepsPerRev,99,99,99,99);
  motor() {}

  motor(int a, int b, int c, int d){
      Stepper  f (stepsPerRev, a , c , b , d ); //isto nao pode ser a melhor maneira, esta-me a falhar algo...
      stepper =  f;
      
      pins[0]=a;pins[1]=b;pins[2]=c;pins[3]=d;
      currentPos=targetPos=0;
  }

  void setTarget(int target) { targetPos = target;}

  void step() {
    Serial.write("Step Func\n");
    Serial.write(currentPos);
    if (currentPos==1024){
        currentPos=0;
        Serial.write("Position restart\n");
      }

    if (currentPos != targetPos){
        stepper.step(1);
        currentPos++;
        Serial.write("Step!\n");
    } 
  }

};

struct motor motors[nrMotors];

//1 2 
//3 4
//5 6
//fist minutos second hours

void createMotor() {
  motors[0] = motor(31, 33, 35, 37);
  //todo resto dos motores
}

void motorSetup() {
  for (int i = 0; i < nrMotors; i++) {
    motors[i].stepper.setSpeed(RPM);
  }
}


void setup()
{
  Serial.begin(9600);
  Serial.write("Starting setup\n");
  
  
  createMotor();
  motorSetup();
  delay(5000);
  motors[0].targetPos=512;



 Serial.write("Exiting setup\n");

}



void loop() {
  Serial.write("Loop\n");
  for (int i = 0; i < nrMotors; i++) {
     motors[i].step();
  }
  //delay(50);

}


