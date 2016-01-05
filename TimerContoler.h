// TimerContoler.h

#ifndef _TIMERCONTOLER_h
#define _TIMERCONTOLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Command.h"

class TimerContoler 
{
public :
	bool processCommand(const Command &command, String &response);

};

extern TimerContoler timerContoler;

#endif

