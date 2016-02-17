// Zone.h

#ifndef _ZONE_h
#define _ZONE_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

struct ZoneConfig
{
	unsigned long TimeOut = 7;
	bool OffByTime = false;
	uint8_t OffHour = 0;
	uint8_t OffMin = 0;
};

class Zone
{
private:
	
	unsigned long _lastMovementOnMillis = 0;
	void checkStateByMovement();


public:
	uint8_t _pinMotionSensor = 0;
	uint8_t _pinLight = 0;
	ZoneConfig Config;
	
	String Name;
	bool IsLightOn = false;
	bool IsManualMode = false;
	//Zone();
	Zone(String name);
	Zone& operator=(String name);
	void setup(uint8_t pinMotionSensor, uint8_t pinLight);
	void turnLightON();
	void turnLightOFF();
	unsigned long turnOffAfter();
	void printInfo();
	void checkState(bool isDark, uint8_t hour, uint8_t min);
};



#endif

