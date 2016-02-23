// Command.h

#ifndef _COMMAND_h
#define _COMMAND_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Command
{
	String _params;

public:
	String Name;
	String get(String key);
	const char* getChar(String key);
	int getInt(String key);
	bool getBool(String key);
	bool parse(String line);

	void free();
};

extern Command command;

#endif

