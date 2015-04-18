#ifndef DRIVE_H
#define DRIVE_H
#include <AFMotor.h>
#include <Encoder.h>

class Drive{
	public:
		Drive(AF_DCMotor *f, AF_DCMotor * r, Encoder * e);
		Drive(AF_DCMotor *f, AF_DCMotor * r, Encoder * e, byte (*a)(int), byte (*b)(int));
		void setPower(byte);
		void setLinearPower(byte);
		void reset();
	private:
		AF_DCMotor * front;
		AF_DCMotor * rear;
		byte (*linearizeFront)(byte);
		byte (*linearizeRear)(byte);
		Encoder * encoder;
};

#endif