// MotionSensor.h

#ifndef _MOTIONSENSOR_h
#define _MOTIONSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class MotionSensor
{
private: 
	uint8_t _pinMotionSensor;
	unsigned long _lastMovementOnMillis = 0;


public:
	String Name;
	MotionSensor(String name);
	unsigned long TimeOut = 7;
	void setup(uint8_t pinIn);
	bool wasMovement();
	unsigned long timeOutAfter();
	void printInfo();
};


#endif

