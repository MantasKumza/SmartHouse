
#include "OutdoorLightControl.h"
#include "LightSensor.h"
#include "Ethernet.h"
#include <Wire.h>
#include <Sodaq_DS3231.h>


Zone* OutdoorLightControl::getZoneByName(String zoneName)
{
	for (int i = 0; i < _zonesCount; i++)
	{
		if (_zones[i]->Name == zoneName)
		{
			return _zones[i];
		}
	}
}
void OutdoorLightControl::begin()
{
	_zones[0] = _zoneTerrace;
	_zones[1] = _zoneSummerhouse;
	_zones[2] = _zoneFireplace;
	_zones[3] = _zoneDriveWay;

	rtc.begin();
}
void OutdoorLightControl::setupZone(uint8_t pinMotionSensor, uint8_t pinLight, String zoneName)
{
	Zone* zone = getZoneByName(zoneName);
	zone->setup(pinMotionSensor, pinLight);
}
void OutdoorLightControl::setupLightSensor(uint8_t pinNo, int darkFrom)
{
	lightSensor.setup(pinNo);
	lightSensor.IsDarkFrom = darkFrom;
}
bool OutdoorLightControl::isDark()
{
	return lightSensor.isDark();
}
void OutdoorLightControl::checkState()
{
	DateTime time = rtc.now();
	bool isDark = true;//this->isDark();

	_zoneTerrace->checkState(isDark, time.hour(), time.minute());
	_zoneSummerhouse->checkState(isDark, time.hour(), time.minute());
	_zoneDriveWay->checkState(isDark, time.hour(), time.minute());

	if (isDark && (_zoneSummerhouse->IsLightOn || _zoneTerrace->IsLightOn))
	{
		_zoneFireplace->turnLightON();
	}
	else
	{

		_zoneFireplace->checkState(isDark, time.hour(), time.minute());
	}
}


bool OutdoorLightControl::processCommand(const Command &command, String &response)
{

	Serial.println(String("Command=") + command.Name);
	if (command.Name == "SaveZoneConfig")
	{
		return true;
	}
	else if (command.Name == "SaveZoneConfig")
	{
		return true;
	}
	else if (command.Name == "GetZonesState")
	{
		response = "[";
		for (int i = 0; i < _zonesCount; i++)
		{
			response += "{";
			response += "\"ZoneName\":\"" + _zones[i]->Name + "\",";
			response += "\"IsLightOn\":" + toString(_zones[i]->IsLightOn) + ",";
			response += "\"IsManualMode\":" + toString(_zones[i]->Config.IsManualMode);
			response += "}";
			if (i != _zonesCount - 1)
				response += ",";
		}
		response += "]";
		return true;
	}
	else if (command.Name == "SwitchManualMode")
	{
		//line += "\"TimeOut\":\"" + String(zone->Config.TimeOutSeconds) + "\",";
		//line += "\"TurnOffHour\":\"" + String(zone->Config.OffTimeHour) + "\",";
		//line += "\"TurnOffMin\":\"" + String(zone->Config.OffTimeMin) + "\"";
		return true;
	}
	else if (command.Name == "SwitchLight")
	{
		return true;
	}
	return false;
}
String OutdoorLightControl::toString(bool value)
{
	if (value)
		return "true";
	else
		return "false";
}



OutdoorLightControl outdoorLightControl;

