// 
// 
// 

#include "BlinkControl.h"

void BlinkControl::setup(uint8_t pinOut)
{
	_pinOut = pinOut;
	pinMode(_pinOut, OUTPUT);
}

void BlinkControl::blink()
{
	unsigned long timeSpan = millis() - _lastMillis;
	if (timeSpan > 1000)
	{
		_lastMillis = millis();
		_lastOutValue = !_lastOutValue;
		if (_lastOutValue)
			digitalWrite(_pinOut, HIGH);
		else
			digitalWrite(_pinOut, LOW);
	}
}


BlinkControl blinkControl;

