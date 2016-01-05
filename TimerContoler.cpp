// 
// 
// 

#include "TimerContoler.h"
#include <Sodaq_DS3231.h>

bool TimerContoler::processCommand(const Command &command, String &response)
{
	if (command.Name == "SetTime")
	{
		return true;
	}
	if (command.Name == "PrintTime")
	{
		DateTime t = rtc.now();
		response = String("Now is: ") + t.year() + "." + t.month() + "." + t.date() + " " + t.hour() + ":" + t.minute() + ":" + t.second();
		return true;
	}
	else if (command.Name == "UpdateTime")
	{
		return true;
	}
	return false;
}

TimerContoler timerContoler;

