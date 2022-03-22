#include "Arduino.h"
#include "Dto.h"
#include <ArduinoJson.h>

void Dto::setLap(int lap){
    this->lap = lap;
}
int Dto::getLap(){
    return this->lap;
};


void Dto::setDirection(int direction){
    this->direction = direction;
};

int Dto::getDirection(){
    return this->direction;
};


void Dto::setShortest(int shortest){
    this->shortest = shortest;
};

int Dto::getShortest(){
    return this->shortest;
};


void Dto::setData(int pos, int data){
    this->data[pos] = data;
};

void Dto::setData(int* array){
    for(int i=0; i<12; i++){
        this->data[i] = array[i];
    }
};

int Dto::Dto::Dto::getData(int pos){
    return this->data[pos];
};


String Dto::getBytes(){
    DynamicJsonDocument doc(1024);    
    doc["lap"] = lap;
    doc["shortest"] = shortest;
    doc["direction"] = direction;
    for (int i=0; i<12; i++){
        doc["data"][i] = data[i];
    }
    char buffernew[256];
    serializeJson(doc, buffernew);

    String s = "";
    int i = 0;
    while (i<256) {
        s = s + buffernew[i];
        if(buffernew[i] == '}') {break;}
        i++;
    };
    return s;
};

void Dto::setDto(String input){
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, input);    
    this->lap=  doc["lap"];
    this->shortest = doc["shortest"];   
    this->direction = doc["direction"];
    for (int i=0; i<12; i++){
        this->data[i] = doc["data"][i];
    }
};

