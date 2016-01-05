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

}

void Zone::checkStateByMovement()
{
 
  int isMovement = digitalRead(_pinMotionSensor);
  if (isMovement == HIGH)
  {
    _lastMovementOnMillis = millis();
    turnLightON();
  }
  else
  {
    unsigned long timeSpan = millis() - _lastMovementOnMillis;
    if (timeSpan > Config.TimeOutSeconds * 1000)
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

  if (!Config.IsManualMode)
  {
    if (isDark)
    {
      if (Config.IsTurnOffByTime)
      {
        if (hour >= Config.OffTimeHour && min >= Config.OffTimeMin)
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
};


