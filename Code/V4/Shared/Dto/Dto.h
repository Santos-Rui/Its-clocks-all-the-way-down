#include "Arduino.h"
#include <ArduinoJson.h>
#pragma once

class Dto {
    private:
        int shortest; 
        int direction;
        int lap;
        int data[12];

    public:
        void setLap(int lap);
        int getLap();
        void setDirection(int direction);
        int getDirection();
        void setShortest(int shortest);
        int getShortest();
        void setData(int pos, int data);
        void setData(int* pos);
        int getData(int pos);
        String getBytes();
        void setDto(String);
};

