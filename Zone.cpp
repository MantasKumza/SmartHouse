#include "Zone.h"

Zone::Zone(String name)
{
	Name = name;
}
Zone& Zone::operator=(String name)
{
	Name = name;
	return *this;
}
void Zone::setup(uint8_t pinMotionSensor, uint8_t pinLight)
{
	_pinMotionSensor = pinMotionSensor;
	_pinLight = pinLight;
	pinMode(_pinMotionSensor, INPUT_PULLUP);
	pinMode(_pinLight, OUTPUT);
	turnLightON();
	delay(200);
	turnLightOFF();

}

void Zone::checkStateByMovement()
{

	int isMovement = digitalRead(_pinMotionSensor);
	if (isMovement == LOW)
	{
		_lastMovementOnMillis = millis();
		turnLightON();
	}
	else
	{
		unsigned long timeSpan = millis() - _lastMovementOnMillis;
		if (timeSpan > Config.TimeOut * 1000)
		{
			turnLightOFF();
		}

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
void Zone::checkState(bool isDark, uint8_t hour, uint8_t min)
{

	if (!IsManualMode)
	{
		if (isDark)
		{
			if (Config.OffByTime)
			{
				if (hour >= Config.OffHour && min >= Config.OffMin)
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
	Serial.println(String("Zone ") + Name);
	Serial.println(String("   Motion sensor pin=") + _pinMotionSensor);
	Serial.println(String("   Light pin=") + _pinLight);
	Serial.println(String("   TimeOut=") + Config.TimeOut);
	Serial.println(String("   OffByTime=") + Config.OffByTime);
	Serial.println(String("   Off Time=") + Config.OffHour+":"+Config.OffMin);
	

};
unsigned long Zone::turnOffAfter()
{
	return millis() - _lastMovementOnMillis;
}

