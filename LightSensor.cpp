// 
// 
// 

#include "LightSensor.h"

void LightSensor::setup(uint8_t pinNo)
{
	_pinNo = pinNo;
	pinMode(_pinNo, INPUT);

}
bool LightSensor::isDark()
{
	int value = analogRead(_pinNo);
 //  Serial.println(String("LightSensor: Pin=")+_pinNo+" Value="+ value+" Drak From"+IsDarkFrom);
	return value < IsDarkFrom;
}


LightSensor lightSensor;

