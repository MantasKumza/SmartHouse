// WebService.h

#ifndef _WEBSERVICE_h
#define _WEBSERVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EthernetServer.h"
#include "IPAddress.h"
#include "CommandProcessor.h"
#include "Constants.h"

#define REQ_BUF_SZ   20

class WebService
{
private: 
	String _readString;
	EthernetServer server=80;
	char HTTP_req[REQ_BUF_SZ] = { 0 }; // buffered HTTP request stored as null terminated string
	char req_index = 0;
	
	String isRequestedFile(String &request);
	void sendFile(EthernetClient &client,const String &fileName);
	void sendResponseAsJson(EthernetClient &client,const String &response,bool isHtml);
 public:
	 CommandProcessor* CommandProcessors[CMD_PROC_COUNT];
	 void begin(IPAddress ip, IPAddress dnsAndGateway);
	 void listenForClient();

};

extern WebService webService;

#endif

