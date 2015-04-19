#ifndef ENCODER_H
#define ENCODER_H
#include <Arduino.h>
#define CLICK_TO_DISTANCE 1

class Encoder{
	public:
		Encoder(byte, byte);
		void update();
		void reset();
		float getPosition();
		float getDelta();
	private:
		float pos;
		float lastPos;
		byte pinA;
		byte pinB;
		byte last;
		byte n;
};

#endif