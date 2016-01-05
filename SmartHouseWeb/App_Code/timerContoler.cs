using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Summary description for timerContoler
/// </summary>
public class timerContoler
{
	public static bool processCommand(Command command, ref string response)
{
	if (command.Name == "SetTime")
	{
		return true;
	}
	if (command.Name == "PrintTime")
	{
		DateTime t = DateTime.Now;
		//response = String("Now is: ") + t.year() + "." + t.month() + "." + t.date() + " " + t.hour() + ":" + t.minute() + ":" + t.second();
		return true;
	}
	else if (command.Name == "UpdateTime")
	{
		return true;
	}
	return false;
}
}