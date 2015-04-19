#ifndef DRIVE_CPP
#define DRIVE_CPP
#include "Drive.h"

Drive::Drive(AF_DCMotor *f, AF_DCMotor * r, Encoder * e, PID * p){
	this->front = f;
	this->rear = r;
	this->encoder = e;
	this->controller = p;
}

Drive::Drive(AF_DCMotor *f, AF_DCMotor * r, Encoder * e, PID * p, byte (*a)(byte), byte (*b)(byte)){
	this->front = f;
	this->rear = r;
	this->encoder = e;
	this->controller = p;
	this->linearizeFront = a;
	this->linearizeRear = b;
}

void Drive::setLinearPower(int signal){
	byte fSignal = (byte)abs(signal);
	byte rSignal = (byte)abs(signal);
	if(this->linearizeFront && this->linearizeRear){
		fSignal = this->linearizeFront(fSignal);
		rSignal = this->linearizeRear(rSignal);
	}
	this->front->run((signal > 0)? FORWARD : BACKWARD);
	this->rear->run((signal > 0)? FORWARD : BACKWARD);
	this->front->setSpeed(min(fSignal,255));
	this->rear->setSpeed(min(rSignal,255));
}

void Drive::setPower(int signal){
	byte fSignal = (byte)abs(signal);
	byte rSignal = (byte)abs(signal);
	this->front->run((signal > 0)? FORWARD : BACKWARD);
	this->rear->run((signal > 0)? FORWARD : BACKWARD);
	this->front->setSpeed(min(fSignal,255));
	this->rear->setSpeed(min(rSignal,255));
}

void Drive::reset(){
	this->front->run(RELEASE);
	this->rear->run(RELEASE);
	this->front->setSpeed(0);
	this->rear->setSpeed(0);
	this->encoder->reset();
}

#endif