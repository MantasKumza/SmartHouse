#include "JsonResponse.h"
#include "OutdoorLightControl.h"
#include "LightSensor.h"
#include "Ethernet.h"
#include <Wire.h>
#include <Sodaq_DS3231.h>
#include "EEPROM.h"




void OutdoorLightControl::begin()
{

	_zones[0] = new Zone(Zone_TerraceDown);
	_zones[1] = new Zone(Zone_TerraceGround);
	_zones[2] = new Zone(Zone_ArborDown);
	_zones[3] = new Zone(Zone_ArborGround);
	_zones[4] = new Zone(Zone_ActivePlace);
	_zones[5] = new Zone(Zone_DriveIn);
	_zones[6] = new Zone(Zone_Waterfall);

	_motionSensors[0] = new MotionSensor(MotionSensor_Terrace);
	_motionSensors[1] = new MotionSensor(MotionSensor_Arbor);
	_motionSensors[2] = new MotionSensor(MotionSensor_DriveIn);
	_motionSensors[3] = new MotionSensor(MotionSensor_ActivePlace);

	relate(Zone_TerraceDown, MotionSensor_Terrace);
	relate(Zone_TerraceGround, MotionSensor_Terrace);

	relate(Zone_ArborDown, MotionSensor_Arbor);
	relate(Zone_ArborGround, MotionSensor_Arbor);

	relate(Zone_ActivePlace, MotionSensor_ActivePlace);

	relate(Zone_DriveIn, MotionSensor_DriveIn);
	relate(Zone_Waterfall, MotionSensor_DriveIn);
	//EEPROM.put<ZoneConfig>(0, _zoneTerrace->Config);
	//EEPROM.put<ZoneConfig>(20, _zoneSummerhouse->Config);
	//EEPROM.put<ZoneConfig>(40, _zoneFireplace->Config);
	//EEPROM.put<ZoneConfig>(60, _zoneDriveWay->Config);

	/*EEPROM.get<ZoneConfig>(0, _zoneTerrace->Config);
	EEPROM.get<ZoneConfig>(20, _zoneSummerhouse->Config);
	EEPROM.get<ZoneConfig>(40, _zoneFireplace->Config);
	EEPROM.get<ZoneConfig>(60, _zoneDriveWay->Config);*/
}
void OutdoorLightControl::relate(const char *zoneName, const char *motionSensorName)
{
	Zone* zone = getZone(zoneName);
	MotionSensor* motionSensor = getMotionSensor(motionSensorName);
	zone->setMotionSensor(motionSensor);
}
void OutdoorLightControl::setupZone(const char *name, uint8_t pinNo)
{
	Zone* zone = getZone(name);
	zone->setup(pinNo);
}
void OutdoorLightControl::setupMotionSensor(const char *name, uint8_t pinNo)
{
	MotionSensor* motionSensor = getMotionSensor(name);
	motionSensor->setup(pinNo);
}


void OutdoorLightControl::checkState()
{
	bool isDark = lightSensor.isDark();
	for (int i = 0; i < _zonesCount; i++)
	{
		Zone* zone = _zones[i];
		if (zone->getMotionSensorName() == Zone_ActivePlace)
		{
			if (!zone->IsManualMode)
			{
				if (isDark && (getMotionSensor(MotionSensor_Terrace)->wasMovement() || getMotionSensor(MotionSensor_Arbor)->wasMovement()))
				{
					zone->turnLightON();
				}
				else
				{
					zone->checkState(isDark, rtc.now());
				}
			}
		}
		else
		{
			zone->checkState(isDark, rtc.now());
		}

	}
}


bool OutdoorLightControl::processCommand(Command &command, String &response)
{

	JsonResponse json = JsonResponse(response);
	//if (Serial)
//		Serial.println(String("Command=") + command.Name);
	if (command.Name == Cmd_GetZoneConfig)
	{

		Zone* zone = getZone(command.getChar(Name_ZoneName));
		json.start();
		json.append(Name_ZoneName, zone->Name);
		//json.append(Name_TimeOut, zone->Config.TimeOut);
		json.append(Name_OffByTime, zone->Config.OffByTime);
		json.append(Name_OffHour, zone->Config.OffHour);
		json.append(Name_OffMin, zone->Config.OffMin);
		//json.append("TurnOffAfter", zone->turnOffAfter());
		json.end();
		return true;
	}
	else if (command.Name == Cmd_SaveZoneConfig)
	{
		Zone* zone = getZone(command.getChar(Name_ZoneName));
		zone->Config.OffByTime = command.getBool(Name_OffByTime);
		zone->Config.OffHour = command.getInt(Name_OffHour);
		zone->Config.OffMin = command.getInt(Name_OffMin);
		//zone->Config.TimeOut = command.getInt(Name_TimeOut);
		return true;
	}
	else if (command.Name == Cmd_GetZonesState)
	{
		response = "[";
		for (int i = 0; i < _zonesCount; i++)
		{
			Zone* zone = _zones[i];
			json.start();
			json.append(Name_ZoneName, zone->Name);
			json.append(Name_IsLightOn, zone->IsLightOn);
			json.append(Name_IsManualMode, zone->IsManualMode);
			json.end();

			if (i != _zonesCount - 1)
				response += ",";
		}
		response += "]";
		return true;
	}
	else if (command.Name == Cmd_SwitchManualMode)
	{
		Zone* zone = getZone(command.getChar(Name_ZoneName));
		zone->IsManualMode = !zone->IsManualMode;
		json.start();
		json.append(Name_ZoneName, zone->Name);
		json.append(Name_IsManualMode, zone->IsManualMode);
		json.end();
		return true;
	}
	else if (command.Name == Cmd_SwitchLight)
	{
		Zone* zone = getZone(command.get(Name_ZoneName).c_str());
		if (zone->IsManualMode)
		{
			if (zone->IsLightOn)
				zone->turnLightOFF();
			else
				zone->turnLightON();
		}
		json.start();
		json.append(Name_ZoneName, zone->Name);
		json.append(Name_IsLightOn, zone->IsLightOn);
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
Zone* OutdoorLightControl::getZone(const char *name)
{
	for (int i = 0; i < _zonesCount; i++)
	{
		if (_zones[i]->Name == name)
		{
			return _zones[i];
		}
	}
}
MotionSensor* OutdoorLightControl::getMotionSensor(const char *name)
{
	for (int i = 0; i < _motionSensorsCount; i++)
	{
		if (_motionSensors[i]->Name == name)
		{
			return _motionSensors[i];
		}
	}
}


OutdoorLightControl outdoorLightControl;

