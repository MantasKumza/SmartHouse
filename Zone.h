// Zone.h

#ifndef _ZONE_h
#define _ZONE_h


#include "arduino.h"
#include <string.h>

struct ZoneConf
{
	bool IsManualMode = false;
	bool IsTurnOffByTime = false;
	uint8_t OffTimeHour = 0;
	uint8_t OffTimeMin = 0;
	unsigned long TimeOutSeconds = 7;
};

class Zone
{
private:
	
	unsigned long _lastMovementOnMillis = 0;
	

	void checkStateByMovement();


public:
	uint8_t _pinMotionSensor = 0;
	uint8_t _pinLight = 0;
	ZoneConf Config;
	String Name;
	bool IsLightOn = false;

	//Zone();
	Zone(String name);
	Zone& operator=(String name);
	void setup(uint8_t pinMotionSensor, uint8_t pinLight);
	void turnLightON();
	void turnLightOFF();


	void checkState(bool isDark, uint8_t hour, uint8_t min);
};



#endif

