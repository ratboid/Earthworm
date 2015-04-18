#include <Servo.h>

#ifndef EYESTALK_H
#define EYESTALK_H

class EyeStalk {
  private:
    int pingPin;
    int servoPin;
    Servo servo;
    long duration;
    long mstocm(long microsecs);
    long mstoin(long microsecs);
    
   public:
     EyeStalk(int usPin, int svPin);
     void servoWrite(int theta);
     int servoRead();
     int getDistance();
};

#endif