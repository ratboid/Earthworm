#ifndef PID_CPP
#define PID_CPP
#include "PID.h"
#define dt 0.001

PID::PID(float kP, float kI, float kD){
	this->kP = kP;
	this->kI = kI;
	this->kD = kD;
	this->reset();
}

int PID::step(float curr, float goal){
	float error = goal - curr;
	this->sumError += error;
	int signal = (int) (this->kP * error) + (this->kI * sumError) + (this->kD * (error - this->lastError) * dt);
	this->lastError = error;
	return signal;
}

void PID::reset(){
	this->lastError = 0.0;
	this->sumError = 0.0;
}


#endif