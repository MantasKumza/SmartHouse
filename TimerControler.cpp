// 
// 
// 

#include "TimerControler.h"
#include <Sodaq_DS3231.h>

bool TimerControler::processCommand(Command &command, String &response)
{

	if (command.Name == "SetTime")
	{
		return true;
	}
	if (command.Name == "PrintTime")
	{
		response = "{DateTime:";
		rtc.now().addToString(response);
		response += "}";
		return true;
	}
	else if (command.Name == "UpdateTime")
	{
		return true;
	}
	return false;
}
void TimerControler::printInfo()
{
	String value = "TimerControler now is: ";
	rtc.now().addToString(value);
	Serial.println(value);

}

TimerControler timerControler;

