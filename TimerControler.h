
#ifndef _TIMERCONTOLER_h
#define _TIMERCONTOLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Command.h"
#include "CommandProcessor.h"


class TimerControler : public CommandProcessor
{
public :
	virtual bool processCommand(Command &command, String &response);
	void printInfo();

};

extern TimerControler timerControler;

#endif

