// CommandProcessor.h

#ifndef _COMMANDPROCESSOR_h
#define _COMMANDPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Command.h"

class CommandProcessor
{

public:
	virtual bool processCommand(Command &command, String &response);


};


#endif

