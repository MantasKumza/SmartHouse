// LightSensor.h

#ifndef _LIGHTSENSOR_h
#define _LIGHTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LightSensor
{
private:
	uint8_t _pinNo;

public:
	void setup(uint8_t pinNo);
	bool isDark();
	int IsDarkFrom = 0;
};

extern LightSensor lightSensor;

#endif

