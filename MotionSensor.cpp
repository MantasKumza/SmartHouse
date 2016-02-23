// 
// 
// 

#include "MotionSensor.h"
MotionSensor::MotionSensor(const char *name)
{
	Name = name;
}
void MotionSensor::setup(uint8_t pinIn)
{
	_pinMotionSensor = pinIn;
	pinMode(_pinMotionSensor, INPUT_PULLUP);
	
}
bool MotionSensor::wasMovement()
{
	int value = digitalRead(_pinMotionSensor);
	if (value == LOW)
	{
		_lastMovementOnMillis = millis();
		_wasMove = true;
	}
	else
	{
		unsigned long timeSpan = millis() - _lastMovementOnMillis;
		if (timeSpan > TimeOut * 1000)
		{
			_wasMove = false;
		}

	}
	return _wasMove;
	
}



