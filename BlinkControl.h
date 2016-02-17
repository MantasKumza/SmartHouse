// BlinkControl.h

#ifndef _BLINKCONTROL_h
#define _BLINKCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class BlinkControl
{
 private:
	 uint8_t _pinOut;
	 bool _lastOutValue = false;
	 unsigned long _lastMillis = 0;

 public:
	 void setup(uint8_t pinOut);
	 void blink();
};

extern BlinkControl blinkControl;

#endif

