#include "Zone.h"

Zone::Zone(const char *name)
{
	Config.Name = name;
	Name = name;
}

void Zone::setMotionSensor(MotionSensor *motionSensor)
{
	
	_motionSensor = motionSensor;
}
void Zone::setup(uint8_t pinLight)
{

	_pinLight = pinLight;
	pinMode(_pinLight, OUTPUT);
	turnLightON();
	delay(200);
	turnLightOFF();

}

void Zone::checkStateByMovement()
{
	if (_motionSensor == nullptr) return;
	if (_motionSensor->wasMovement())
	{
		turnLightON();
	}
	else
	{
		turnLightOFF();
	}
}
void Zone::turnLightOFF()
{
	digitalWrite(_pinLight, LOW);
	IsLightOn = false;
};
void Zone::turnLightON()
{

	digitalWrite(_pinLight, HIGH);
	IsLightOn = true;
};
void Zone::checkState(bool isDark, DateTime time)
{

	if (!IsManualMode)
	{
		if (isDark)
		{
			if (Config.OffByTime)
			{
				if (time.hour() >= Config.OffHour && time.minute() >= Config.OffMin)
				{
					checkStateByMovement();
				}
				else
				{
					turnLightON();
				}
			}
			else
			{
				checkStateByMovement();
			}

		}
		else
		{
			turnLightOFF();
		}
	}
}

void Zone::printInfo()
{
	if (Serial)
	{
		Serial.println(String("Zone ") + Name);
		Serial.println(String("   Light Pin=") + _pinLight);
		Serial.println(String("   Off By Time=") + Config.OffByTime);
		Serial.println(String("   Off Time=") + Config.OffHour + ":" + Config.OffMin);
		if (_motionSensor == nullptr)
		{
			Serial.println("   Motion Sensor=None;");
		}
		else
		{
			Serial.println(String("   MotionSensor=") + _motionSensor->Name + " TimeOut=" + _motionSensor->TimeOut);
		}
	}
};
const char* Zone::getMotionSensorName()
{
	if (_motionSensor == nullptr) return "";
	return _motionSensor->Name;
}


