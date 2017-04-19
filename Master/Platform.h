/*
  Pump.h
  Created by Pietro Rustici, 14 April, 2017.
  Released into the public domain.
*/
#ifndef Platform_h
#define Platform_h

#include "Arduino.h"

class Platform
{
  public:
    Platform(int enable,int step, int dir, int max_tubes, int steps_per_tube);
    void goTo(int pos);
    void setSteps(int steps);
  private:
    int _enable;
    int _step;
    int _dir;
    int _steps_per_tube;
    int _current_tube;
    int _max_tubes;
};

#endif
