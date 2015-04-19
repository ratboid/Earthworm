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
	byte fSignal = (byte)min(abs(signal),255);
	byte rSignal = (byte)min(abs(signal),255);
	if(this->linearizeFront && this->linearizeRear){
		fSignal = this->linearizeFront(fSignal);
		rSignal = this->linearizeRear(rSignal);
	}
	this->front->run((signal > 0)? FORWARD : BACKWARD);
	this->rear->run((signal > 0)? FORWARD : BACKWARD);
	this->front->setSpeed(fSignal);
	this->rear->setSpeed(rSignal);
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
	this->controller->reset();
	this->goal = 0;
}

void Drive::step(){
	float curr = this->encoder->getPosition();
	int signal = this->controller->step(curr,this->goal);
	this->setLinearPower(signal);
}

float Drive::getError(){
	return this->goal - this->encoder->getPosition();
}

void Drive::setGoal(float g){
	this->reset();
	this->goal = g;
}

#endif