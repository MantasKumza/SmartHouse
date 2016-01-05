// 
// 
// 

#include "Command.h"

bool Command::parse(String line)
{
  int index= line.indexOf("Command");
  if (index >= 0)
  {
	  _params = line;
	  Name = get("Command");
	  return true;
  }
  else
  {
	  return false;
  }
}
String Command::get(String key)
{

	String value;
	key += "=";
	int index = _params.indexOf(key);

	if (index > -1)
	{
		int indexStart = index + key.length();

		int indexEnd = _params.indexOf("&", indexStart);
		if (indexEnd<0)
			indexEnd = _params.indexOf(" ", indexStart);
		if (indexEnd < 0)
			indexEnd = _params.length();


		value = _params.substring(indexStart, indexEnd);
	}

	return value;
}
int Command::getInt(String key)
{
	return get(key).toInt();
}
void Command::free()
{
	Name = "";
	_params = "";
}


Command command;

