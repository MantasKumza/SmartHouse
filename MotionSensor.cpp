// 
// 
// 

#include "MotionSensor.h"

void MotionSensor::setup(uint8_t pinIn)
{
	_pinMotionSensor = pinIn;
	pinMode(_pinMotionSensor, INPUT_PULLUP);

}



