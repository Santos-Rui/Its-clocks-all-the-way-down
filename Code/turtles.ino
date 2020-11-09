//  code for the V3 clock

#include <Stepper.h>

const int stepsPerRev = 2048; // change this to fit the number of steps per revolution
const int RPM = 15;           // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int lap = 4096;
const int nrMotors = 12;


//int numeros[12];
//numeros[0]=[0,0,0,0,0,0,0,0,0,0,0,0,];

struct motor {
  	int currentPos = 0;
 	int targetPos = 0;
 	int lap = 0;
  	int pins[4];
	Stepper stepper = Stepper(stepsPerRev,95,97,96,98);
 	
 	motor() {}

 	motor(int a, int b, int c, int d){
      	Stepper  f (stepsPerRev, d , c , b , a ); 
      	stepper =  f;
      	//isto nao pode ser a melhor maneira, esta-me a falhar algo...

        pins[0]=a;pins[1]=b;pins[2]=c;pins[3]=d;
      	currentPos=targetPos=lap=0;
  	}

  	void setTarget(int target) {
  		if(target>=currentPos){lap=1;}  //se tivermos a fretne temos de dar a volta
  		targetPos = target;
  	}

  	void step() {
    	//Serial.write("Step Func\n");
    	//Serial.write(currentPos);

    	if (currentPos==lap){
        	currentPos=0;
        	lap--;
        	//Serial.write("Position restart\n");
      	}

    	if (lap > 0 || currentPos < targetPos){
     	   stepper.step(1);
     	   currentPos++;
     	   //Serial.write("Step!\n");
    	} 
 	}
};



//array with the motors themselves. Estou a duplicar a memoria necessaria?
struct motor motors[nrMotors];
//1 2 
//3 4
//5 6



void createMotor() {
	motors[0] = motor( 14  , 15 ,  16, 17 );  //1 top       
	motors[1] = motor( 22 ,  24  ,26 , 28 );  //1 bottom   
	
	motors[2] = motor( 2  ,  3  , 4  ,  5 );  //2 top         
	motors[3] = motor( 6 ,   7  ,  8 ,  9 );  //2 bottom     
	
	motors[4] = motor( 23 ,  25 , 27 , 29 );  //3 top       
	motors[5] = motor( 38 ,  40  ,42 , 44 );  //3 bottom
	
	motors[6] = motor( 10 ,  11 , 12 , 13 );  //4 top           
	motors[7] = motor( 46 , 48  , 50 , 52 );  //4 bottom  
	
	motors[8] = motor( A0,  A1 ,  A2,  A3 );  //5 top    
	motors[9] = motor( A4,  A5 ,  A6 , A7 );  //5 bottom 
	
	motors[10] = motor( A8,  A9 , A10, A11 );  //6 top        
	motors[11] = motor( A12,  A13, A14, A15);  //6 bottom     
}


void motorSetup() {
  for (int i = 0; i < nrMotors; i++) {
    motors[i].stepper.setSpeed(RPM);
  }
}

void turnOffAll(){
	for (int i = 0; i < nrMotors; i++) {
    	digitalWrite(motors[i].pins[0], LOW);
        digitalWrite(motors[i].pins[1], LOW);
        digitalWrite(motors[i].pins[2], LOW);
        digitalWrite(motors[i].pins[3], LOW);
  	}
}


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
  	delay(2000);
  
 	//Serial.write("Exiting setup\n");
 	for(int a=0;a<1;a++){
 		motors[a].setTarget(lap/2);
 	}
}



void loop() {
  	//Serial.write("Loop\n");
	moveAll();
}


