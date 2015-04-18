#ifndef ENCODER_CPP
#define ENCODER_CPP
#include "Encoder.h"

Encoder::Encoder(byte a, byte b){
	this->pinA = a;
	this->pinB = b;
	this->last = LOW;
	this->reset();
}

void Encoder::reset(){
	this->pos = 0;
	this->lastPos = 0;
}

void Encoder::update(){
	this->last = this->last & digitalRead(this->pinA);
	if( (this->last >> 4 == LOW) && (this->last & 15 == HIGH) ){
		if( digitalRead(this->pinB) == LOW ){
			this->pos += CLICK_TO_DISTANCE;
		}else{
			this->pos -= CLICK_TO_DISTANCE;
		}
	}
	this->last = this->last << 4; 
}

float Encoder::getPosition(){
	return this->pos;
}

float Encoder::getDelta(){
	float delta = (this->pos)-(this->lastPos);
	this->lastPos = this->pos;
	return delta;
}

#endif