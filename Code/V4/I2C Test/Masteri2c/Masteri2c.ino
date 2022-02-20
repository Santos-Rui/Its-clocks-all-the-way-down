#include <Stepper.h>
#include <Wire.h>
#include <Dto.h>

using namespace std;
byte x = 0;
byte y = 100;

Dto dto;

void setup(){
    Serial.begin(9600);                                          
    Wire.begin(); // join i2c bus (address optional for master)

    dto.setLap(0);
    dto.setShortest(0);
    dto.setDirection(0);
    dto.setData(0,3);
    dto.setData(1,2);
    
    Serial.println("Exiting setup");
}




void loop() {
  char buffer[128]; 
    
  Serial.println("\n\nloop\n");


  Serial.println("Serializing...");
  String result = dto.getBytes();

  Serial.println("Resulting string is:");
  Serial.println(result);
  
  //Dto dto2;
  //dto2.setDto(result);

  //Serial.println("Resulting dto has data 0:");
  //Serial.println(dto2.getData(0));
  //Serial.println("Resulting dto has data 1:");
  //Serial.println(dto2.getData(1));




  delay(2000);
  

  for(int a=0 ; a < result.length()/32 +1 ; a++){
    
      Wire.beginTransmission(2); // transmit to device #4
      Serial.println("\nNewPackage:");

      for(int s=0 ; s<32 && a*32+s<result.length()  ; s++){
        Serial.print(result[a*32+s]);
        Wire.write(result[a*32+s]);
      }

      Wire.endTransmission();    // stop transmitting

  }



  

  x++;
  y--;
  
  delay(5000);


}
