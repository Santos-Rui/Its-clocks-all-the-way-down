#include "Arduino.h"
#include "Dto.h"

class Dto {
    private:
        bool shortest; //TODO
        int direction;
        bool lap;
        int pos[12];

    public:
        void setLap(bool lap){
            this->lap = lap;
        };
};
