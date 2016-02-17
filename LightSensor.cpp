#include "LightSensor.h"
#include "CommandProcessor.h"
#include "Command.h"

void LightSensor::setup(uint8_t pinIn, uint8_t pinOut, int isDarkFrom)
{
	_pinIn = pinIn;
	_pinOut = pinOut;
	_isDarkFrom = isDarkFrom;
	pinMode(_pinIn, INPUT);
	pinMode(_pinOut, OUTPUT);
}
bool LightSensor::isDark()
{
	int value = analogRead(_pinIn);
	if (value < _isDarkFrom)
	{
		digitalWrite(_pinOut, HIGH);
		return true;
	}
	else
	{
		digitalWrite(_pinOut, LOW);
		return false;
	}
}
bool LightSensor::processCommand(Command &command, String &response)
{
	if (command.Name == "SetIsDarkFrom")
	{
		_isDarkFrom=command.getInt("DarkFrom");
		return true;
	}
	else if (command.Name == "SetIsDarkFrom")
	{
		
		return true;
	}
}
void LightSensor::printInfo()
{
	Serial.println(String("Light sensor: PinIN=") + _pinIn + "; PinOUT" + _pinOut +
		"; Dark from=" + _isDarkFrom + "; Current value=" + analogRead(_pinIn));
}
LightSensor lightSensor;

