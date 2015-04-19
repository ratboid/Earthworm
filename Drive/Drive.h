#ifndef DRIVE_H
#define DRIVE_H
#include <AFMotor.h>
#include <Encoder.h>
#include <Arduino.h>
#include <PID.h>

class Drive{
	public:
		Drive(AF_DCMotor *f, AF_DCMotor * r, Encoder * e, PID * p);
		Drive(AF_DCMotor *f, AF_DCMotor * r, Encoder * e, PID * p, byte (*a)(byte), byte (*b)(byte));
		void setPower(int);
		void setLinearPower(int);
		void reset();
	private:
		AF_DCMotor * front;
		AF_DCMotor * rear;
		PID * controller;
		byte (*linearizeFront)(byte);
		byte (*linearizeRear)(byte);
		Encoder * encoder;
};

#endif