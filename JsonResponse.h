// JSON.h

#ifndef _JSON_h
#define _JSON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class JsonResponse
{
  private: 
	  String _response;
	
  public:
	 JsonResponse(String &response);
	void start();
	void end();
	void append(const char *name, const char *value);
	void append(const char *name, bool value);
	void append(const char *name, unsigned long value);
	void append(const char *name, uint8_t value);
};


#endif

