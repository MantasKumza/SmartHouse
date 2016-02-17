#include "JsonResponse.h"
#include "OutdoorLightControl.h"
#include "LightSensor.h"
#include "Ethernet.h"
#include <Wire.h>
#include <Sodaq_DS3231.h>
#include "EEPROM.h"



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
	//EEPROM.put<ZoneConfig>(0, _zoneTerrace->Config);
	//EEPROM.put<ZoneConfig>(20, _zoneSummerhouse->Config);
	//EEPROM.put<ZoneConfig>(40, _zoneFireplace->Config);
	//EEPROM.put<ZoneConfig>(60, _zoneDriveWay->Config);

	EEPROM.get<ZoneConfig>(0, _zoneTerrace->Config);
	EEPROM.get<ZoneConfig>(20, _zoneSummerhouse->Config);
	EEPROM.get<ZoneConfig>(40, _zoneFireplace->Config);
	EEPROM.get<ZoneConfig>(60, _zoneDriveWay->Config);
}
void OutdoorLightControl::setupZone(uint8_t pinMotionSensor, uint8_t pinLight, String zoneName)
{
	Zone* zone = getZoneByName(zoneName);
	zone->setup(pinMotionSensor, pinLight);
	
}

bool OutdoorLightControl::isDark()
{
	return lightSensor.isDark();
}
void OutdoorLightControl::checkState()
{
	DateTime time = rtc.now();
	bool isDark = lightSensor.isDark();

	_zoneTerrace->checkState(isDark, time.hour(), time.minute());
	_zoneSummerhouse->checkState(isDark, time.hour(), time.minute());
	_zoneDriveWay->checkState(isDark, time.hour(), time.minute());

	if (!_zoneFireplace->IsManualMode)
	{
		if (isDark && (_zoneSummerhouse->IsLightOn || _zoneTerrace->IsLightOn))
		{
			_zoneFireplace->turnLightON();
		}
		else
		{

			_zoneFireplace->checkState(isDark, time.hour(), time.minute());
		}
	}
}


bool OutdoorLightControl::processCommand( Command &command, String &response)
{

	JsonResponse json = JsonResponse(response);
	Serial.println(String("Command=") + command.Name);
	if (command.Name == "GetZoneConfig")
	{

		Zone* zone = getZoneByName(command.get("ZoneName"));
		json.start();
		json.append("ZoneName", zone->Name);
		json.append("TimeOut", zone->Config.TimeOut);
		json.append("OffHour", zone->Config.OffHour);
		json.append("OffMin", zone->Config.OffMin);
		json.append("TurnOffAfter", zone->turnOffAfter());
		json.end();
		return true;
	}
	else if (command.Name == "SaveZoneConfig")
	{
		Zone* zone = getZoneByName(command.get("ZoneName"));
		zone->Config.OffByTime = command.getBool("OffByTime");
		zone->Config.OffHour = command.getInt("OffHour");
		zone->Config.OffMin = command.getInt("OffMin");
		zone->Config.TimeOut = command.getInt("TimeOut");
		return true;
	}
	else if (command.Name == "GetZonesState")
	{
		response = "[";
		for (int i = 0; i < _zonesCount; i++)
		{
			Zone* zone = _zones[i];
			json.start();
			json.append("ZoneName", zone->Name);
			json.append("IsLightOn", zone->IsLightOn);
			json.append("IsManualMode", zone->IsManualMode);
			json.end();

			if (i != _zonesCount - 1)
				response += ",";
		}
		response += "]";
		return true;
	}
	else if (command.Name == "SwitchManualMode")
	{
		Zone* zone = getZoneByName(command.get("ZoneName"));
		zone->IsManualMode = !zone->IsManualMode;
		json.start();
		json.append("ZoneName", zone->Name);
		json.append("IsManualMode", zone->IsManualMode);
		json.end();
		return true;
	}
	else if (command.Name == "SwitchLight")
	{
		Zone* zone = getZoneByName(command.get("ZoneName"));
		if (zone->IsManualMode)
		{
			if (zone->IsLightOn)
				zone->turnLightOFF();
			else
				zone->turnLightON();
		}
		json.start();
		json.append("ZoneName", zone->Name);
		json.append("IsLightOn", zone->IsLightOn);
		json.end();
		return true;
	}
	return false;
}

void OutdoorLightControl::printInfo()
{
	for (int i = 0; i < _zonesCount; i++)
	{
		_zones[i]->printInfo();
	}
}


OutdoorLightControl outdoorLightControl;

