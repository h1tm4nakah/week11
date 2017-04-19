/*
  Pump.cpp
  Created by Pietro Rustici, 14 April, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Platform.h"

Platform::Platform(int enable,int step, int dir, int max_tubes, int steps_per_tube)
{
  pinMode(enable, OUTPUT);
  pinMode(step, OUTPUT);
  pinMode(dir, OUTPUT);
  _enable = enable;
  _step = step;
  _dir = dir;
  _max_tubes = max_tubes;               // set the max number of test tubes the machine can handle
  _steps_per_tube = steps_per_tube;     // how many stepper motor steps are required to go from a test tube to another one 
  _current_tube = 0;                    // track the current test tube
}
void Platform::goTo(int pos)                    // go to a specified test tube
{
  int pos_diff = abs(pos - _current_tube);  // we calculate the difference in position 
  
  if(pos > _current_tube)                   // if the current test tube number is smaller than the  target tube
  {
    digitalWrite(_dir,HIGH);                // we set the stepper motor dir pin high so the platform turn clockwise
  }
  if(pos < _current_tube)                   // if the current test tube number is greater than the  target tube
  {
    digitalWrite(_dir,LOW);                 // we set the stepper motor dir pin low so the platform turn counter-clockwise
  }  
  digitalWrite(_enable,LOW);                // set the stepper driver enable pin LOW so we can move the motor 
  
  for(int i=0; i<_steps_per_tube*pos_diff; i++)    // we move the motor 
   {
      digitalWrite(_step,HIGH);
      delay(5);
      digitalWrite(_step,LOW);
      delay(5);
   }
   _current_tube = pos;
}
void Platform::setSteps(int steps)              // used to tune the number of steps required to move from a test tube to another
{
    _steps_per_tube = steps;
}

