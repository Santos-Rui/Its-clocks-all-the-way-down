#include <Stepper.h>
#pragma once

class CustomStepper{
    private:
        int currentPos = 0;
        int targetPos = 0;
        int direction = 1;
        int lap = 0;
        int pins[4];
        bool doneMoving;
        Stepper * stepper;  

    public:
    
      CustomStepper(int steps, int a, int b, int c, int d);

      void setTarget(int target, bool lap, bool shortest, int direction);

      void setRPM (int RPM);
      
      bool move();
};