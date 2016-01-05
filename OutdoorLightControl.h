// OutdoorLightControl.h

#ifndef _OUTDOORLIGHTCONTROL_h
#define _OUTDOORLIGHTCONTROL_h

#include "arduino.h"
#include "string.h"
#include "Command.h"
#include "zone.h"
#include "Ethernet.h"


class OutdoorLightControl 
{
	

 private:
	 
	 uint8_t _zonesCount = 4;
	 Zone *_zoneTerrace = new Zone("Terrace");
	 Zone *_zoneSummerhouse = new Zone("Summerhouse");
	 Zone *_zoneFireplace = new Zone("Fireplace");
	 Zone *_zoneDriveWay = new Zone("DriveWay");
	 Zone *_zones[4];
	
	 String toString(bool value);
	 Zone* getZoneByName(String zoneName);

 public:

	 
	 void setupZone(uint8_t pinMotionSensor, uint8_t pinLight, String zoneName);
	 void setupLightSensor(uint8_t pinNo,int darkFrom);
	 void begin();
	 void checkState();
	 bool isDark();
	 bool processCommand(const Command &command, String &response);
	
	 
};

extern OutdoorLightControl outdoorLightControl;

#endif

