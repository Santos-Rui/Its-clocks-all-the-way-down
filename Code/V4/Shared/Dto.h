#ifndef Dto_h
#define Dto_h

#include "Arduino.h"

class Dto {
    public:
        void setLap(bool lap); 
    private:
        bool shortest; 
        int direction;
        bool lap;
        int pos[12];     
};
#endif