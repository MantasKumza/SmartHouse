// 
// 
// 

#include "JsonResponse.h"

JsonResponse::JsonResponse(String &response)
{
	_response = response;
}
void JsonResponse::start()
{
	_response += "{";
}
void JsonResponse::end()
{
	if (_response.endsWith(","))
		_response=_response.substring(0, _response.length() - 1);
	_response += "}";
}
void JsonResponse::append(const char *name, const char *value)
{
	_response = _response + "\"" + name + "\":\"" + value + "\",";
}
void JsonResponse::append(const char *name, bool value)
{
	if (value)
		_response = _response + "\"" + name + "\":\"true\",";
	else
		_response = _response + "\"" + name + "\":\"false\",";
}
void JsonResponse::append(const char *name, unsigned long value)
{
	_response = _response + "\"" + name + "\":\"" + value + "\",";
}
void JsonResponse::append(const char *name, uint8_t value)
{
	_response = _response + "\"" + name + "\":\"" + value + "\",";
}



