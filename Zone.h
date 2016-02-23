// Zone.h

#ifndef _ZONE_h
#define _ZONE_h


#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "Config.h"

struct ZoneConfig :public Config
{
	bool OffByTime = false;
	uint8_t OffHour = 0;
	uint8_t OffMin = 0;
};

#include "MotionSensor.h"
#include <Sodaq_DS3231.h>

class Zone
{
private:
	void checkStateByMovement();
	MotionSensor *_motionSensor = nullptr;
	uint8_t _pinLight = 0;
public:
	
	
	ZoneConfig Config;
	
	const char *Name;
	bool IsLightOn = false;
	bool IsManualMode = false;
	
	Zone(const char *name);
	
	void setMotionSensor(MotionSensor *motionSensor);
	void setup(uint8_t pinLight);

	void turnLightON();
	void turnLightOFF();

	void printInfo();
	void checkState(bool isDark, DateTime time);

	const char* getMotionSensorName();
};



#endif

