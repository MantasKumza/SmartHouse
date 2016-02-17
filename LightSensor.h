

#ifndef _LIGHTSENSOR_h
#define _LIGHTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "CommandProcessor.h"
#include "Command.h"

class LightSensor :public CommandProcessor
{
private:
	uint8_t _pinIn;
	uint8_t _pinOut;
	int _isDarkFrom = 0;
public:
	void setup(uint8_t pinIn, uint8_t pinOut, int isDarkFrom);
	bool isDark();
	
	virtual bool processCommand(Command &command, String &response);
	void printInfo();
};

extern LightSensor lightSensor;

#endif

