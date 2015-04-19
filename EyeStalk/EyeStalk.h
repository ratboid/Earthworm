#include <Servo.h>
#include <Arduino.h>
#ifndef EYESTALK_H
#define EYESTALK_H

class EyeStalk {
	private:
		byte pingPin;
		Servo * servo;
		long duration;
		long mstocm(long microsecs);
		long mstoin(long microsecs);
    
	public:
		EyeStalk(int usPin, Servo * servo);
		void servoWrite(int theta);
		int servoRead();
		int getDistance();
};

#endif