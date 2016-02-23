// OutdoorLightControl.h

#ifndef _OUTDOORLIGHTCONTROL_h
#define _OUTDOORLIGHTCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include "arduino.h"
#include "string.h"
#include "Command.h"
#include "zone.h"
#include "Ethernet.h"
#include "CommandProcessor.h"
#include "Constants.h"



class OutdoorLightControl: public CommandProcessor
{
 private:
	 
	 const uint8_t _zonesCount = 7;
	 Zone *_zones[7];
	 const uint8_t _motionSensorsCount = 4;
	 MotionSensor *_motionSensors[4];

	 Zone* getZone(const char *name);
	 MotionSensor* getMotionSensor(const char *name);
	 void relate(const char *zoneName, const char *motionSensorName);


	 void loadZoneConfig(ZoneConfig &zoneConfig);
 public:
	 
	 void setupZone(const char *name, uint8_t pinNo);
	 void setupMotionSensor(const char *name, uint8_t pinNo);

	 void setupLightSensor(uint8_t pinNo,int darkFrom);
	 void begin();
	 void checkState();
	
	 void printInfo();
	 virtual bool processCommand(Command &command, String &response);
	
	 
};

extern OutdoorLightControl outdoorLightControl;

#endif

