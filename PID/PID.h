#ifndef PID_H
#define PID_H

class PID{
	public:
		PID(float, float, float);
		byte step(float, float);
		void reset();
	private:
		float kP, kI, kD;
		float sumError, lastError;
};

#endif