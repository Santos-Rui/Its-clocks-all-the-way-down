//  code for the V3 clock

#include <Stepper.h>
#include <IRremote.h>


const int stepsPerRev = 2048; // change this to fit the number of steps per revolution
const int lapFull = 4096;
const int qlap = 1024;

const int RPM = 15;           // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int nrMotors = 12;

// IR
int RECV_PIN = 34;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
//IR

int rest[12]={0,0,0,0,0,0,0,0,0,0,0,0};
int zero[12]={1024,2048,2048,3072,0,2048,0,2048,0,1024,0,3072};
int um[12]={3584,3584,2048,2048,3584,3584,0,2048,3584,3584,0,0};
int dois[12] = {1024,1024,3072,2048,1024,2048,0,3072,0,1024,3072,3072};
int tres[12] ={1024,1024,3072,2048,1024,1024,3072,0,1024,1024,3072,0};
int quatro[12] ={2048,2048,2048,2048,0,1024,0,2048,3584,3584,0,0};
int cinco[12] ={1024,2048,3072,3072,0,1024,2048,3072,1024,1024,0,3072};
int seis[12] ={1024,2048,3072,3072,0,2048,2048,3072,0,1024,3072,0};
int sete[12] ={1024,1024,3072,2048,3584,3584,2048,0,3584,3584,0,0};
int oito[12] ={1024,2048,2048,3072,0,1024,0,3072,0,1024,0,3072};
int nove[12] ={1024,2048,2048,3072,0,1024,0,2048,1024,1024,0,3072};


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
      if(target<=currentPos){lap=1;}  //se tivermos a fretne temos de dar a volta
      
      targetPos = target;

  }

  void step() {

      if (currentPos==lapFull){
          currentPos=0;
          lap--;
      }
      if (lap > 0 || currentPos < targetPos){
          stepper->step(1);
          currentPos++;
      } 
//      Serial.println("Exiting step  lap =");
//      Serial.println(lap);
//      Serial.println("Cpos =");
//      Serial.println(currentPos);
//      Serial.println("Tpos =");
//      Serial.println(targetPos);
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

void draw(int lista[12]){
  for(int a=0;a<12;a++){
    listaMotors[a]->setTarget(lista[a]);
  }
}

void setup(){
    Serial.begin(9600);

    createMotor();
    motorSetup();
    irrecv.enableIRIn(); // Start  receiver

    delay(2000);
    Serial.println("exiting setup");
}


void loop() {
  if (irrecv.decode(&results)) {
  // if (results.value == 0XFFFFFFFF){
  //   results.value = key_value;
  // }

    switch(results.value){
        
      case 0xFF30CF:    // 1  
      case 0x9716BE3F: 
          draw(um); 
      break;

      case 0xFF18E7:   // 2
      case 0x3D9AE3F7:
          draw(dois); 
      break;

      case 0xFF7A85:   // 3
      case 0x6182021B:
          draw(tres); 
      break;

      case 0xFF10EF:   // 4
      case 0x8C22657B:
          draw(quatro); 
      break;

      case 0xFF38C7:   // 5
      case 0x488F3CBB:
        draw(cinco); 
      break;

      case 0xFF5AA5:   // 6
      case 0x449E79F:
         draw(seis); 
      break;

      case 0xFF42BD:   // 7
          draw(sete);
      break;

      case 0xFF4AB5:   // 8
      case 0xFF1BC01:
          draw(oito);
      break;

      case 0xFF52AD:   // 9
          draw(nove);
      break;

      case 0xFF6897:   // 0
          draw(zero);
      break;



      case 0xFFA25D:   // POWER
          draw(rest);
      break;


      default:
      break;
        }



       
      //Serial.println(results.value, HEX);
      key_value = results.value;
      irrecv.resume();// Receive the next value
  }

  moveAll();
  //delay(30000);
}


