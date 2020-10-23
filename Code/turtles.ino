//  code for the V2 clock

#include <Stepper.h>

const int stepsPerRev = 2048; // change this to fit the number of steps per revolution
const int RPM = 12;           // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int lap = 1024;
const int nrMotors = 12;




struct motor {
  	int currentPos;
 	int targetPos;
  	int pins[4];
	Stepper stepper =  Stepper(stepsPerRev,99,99,99,99);
 	
 	motor() {}

 	motor(int a, int b, int c, int d){
      	Stepper  f (stepsPerRev, a , c , b , d ); //isto nao pode ser a melhor maneira, esta-me a falhar algo...
      	stepper =  f;
      	//stepper.setSpeed(RPM);
     	pins[0]=a;pins[1]=b;pins[2]=c;pins[3]=d;
      	currentPos=targetPos=0;
  	}

  	void setTarget(int target) { targetPos = target;}

  	void step() {
    	//Serial.write("Step Func\n");
    	//Serial.write(currentPos);

    	if (currentPos==1024){
        	currentPos=0;
        	//Serial.write("Position restart\n");
      	}

    	if (currentPos != targetPos){
     	   stepper.step(1);
     	   currentPos++;
     	   //Serial.write("Step!\n");
    	} 
 	}
};


struct motor motors[nrMotors]; //array with the motors themselves. Estou a duplicar a memoria necessaria?
//1 2 
//3 4
//5 6



void createMotor() {
	motors[0] = motor( 31 , 35 , 33 , 37 );  //1 top
	motors[1] = motor( 30 , 34 , 32 , 36 );  //1 bottom
	
	motors[2] = motor( 22 , 26 , 24 , 28 );  //2 top
	motors[3] = motor( 39 , 43 , 41 , 45 );  //2 bottom
	
	motors[4] = motor( 23 , 27 , 25 , 29 );  //3 top
	motors[5] = motor( A0, A2, A1, A3 );     //3 bottom
	
	motors[6] = motor( A12, A14, A13, A15 ); //4 top
	motors[7] = motor( 38 , 42 , 40  , 44 ); //4 bottom
	
	motors[8] = motor(47 , 51 , 49  , 53 );  //5 top
	motors[9] = motor( 46 , 50 , 48  , 52 ); //5 bottom
	
	motors[10] = motor( A8, A10, A9, A11 );  //6 top
	motors[11] = motor( A4, A6, A5, A7 );    //6 bottom
}

void motorSetup() {
  for (int i = 0; i < nrMotors; i++) {
    motors[i].stepper.setSpeed(RPM);
  }
}

void turnOffAll(){}//??

void moveAll(){
	for (int i = 0; i < nrMotors; i++) {
    	motors[i].step();
  	}
}



void setup(){
 	//Serial.begin(9600);
 	//Serial.write("Starting setup\n");

    createMotor();
  	motorSetup();
  	delay(5000);
  
 	//Serial.write("Exiting setup\n");
 	motors[0].targetPos=768;
}



void loop() {
  	//Serial.write("Loop\n");
	moveAll();
  	//delay(50);
}


