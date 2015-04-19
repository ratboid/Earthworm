#ifndef ENCODER_CPP
#define ENCODER_CPP
#include "Encoder.h"

Encoder::Encoder(byte a, byte b){
	this->pinA = a;
	this->pinB = b;
	pinMode(a,INPUT);
	pinMode(b,INPUT);
	this->last = digitalRead(this->pinA);
	this->n = this->last;
	this->reset();
}

void Encoder::reset(){
	this->pos = 0;
	this->lastPos = 0;
}

void Encoder::update(){
	this->n = digitalRead(this->pinA);
	if( this->last == LOW && this->n == HIGH){
		if( digitalRead(this->pinB) == LOW ){
			this->pos += CLICK_TO_DISTANCE;
		}else{
			this->pos -= CLICK_TO_DISTANCE;
		}
		Serial.println(this->pos);
	}
	this->last = this->n;
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