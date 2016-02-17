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
	 
	 uint8_t _zonesCount = 4;
	 Zone *_zoneTerrace = new Zone(Terrace);
	 Zone *_zoneSummerhouse = new Zone(Summerhouse);
	 Zone *_zoneFireplace = new Zone(Fireplace);
	 Zone *_zoneDriveWay = new Zone(DriveIn);
	 Zone *_zones[4];
	
	 String toString(bool value);
	 Zone* getZoneByName(String zoneName);

	 bool isDark();

	 void loadZoneConfig(ZoneConfig &zoneConfig);
 public:

	 
	 void setupZone(uint8_t pinMotionSensor, uint8_t pinLight, String zoneName);
	 void setupLightSensor(uint8_t pinNo,int darkFrom);
	 void begin();
	 void checkState();
	
	 void printInfo();
	 virtual bool processCommand(Command &command, String &response);
	
	 
};

extern OutdoorLightControl outdoorLightControl;

#endif

