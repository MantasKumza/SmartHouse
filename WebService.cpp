#include "WebService.h"
#include "Ethernet.h"
#include "IPAddress.h"
#include "SD.h"
#include "Command.h"
#include "CommandProcessor.h"

void WebService::begin(IPAddress ip, IPAddress dnsAndGateway)
{
	byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //physical mac address
	byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
	Ethernet.begin(mac, ip, dnsAndGateway, dnsAndGateway, subnet);
	server.begin();
	Serial.print("WebService started on ");
	Serial.println(Ethernet.localIP());

	if (!SD.begin(4)) {
		Serial.println("SD initialization failed!");
		return;
	}
	Serial.println("SD initialization done.");

}


void  WebService::listenForClient()
{
	EthernetClient client = server.available();  // try to get client

	if (client) {  // got client?
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {   // client data available to read
				char c = client.read(); // read 1 byte (character) from client
				_readString += c;

				if (c == '\n' && currentLineIsBlank)
				{
					if (_readString.length() > 0)
					{
						if (command.parse(_readString))
						{
							Serial.println(String("Command=") + command.Name);
							String response;
							for (int i = 0; i < CMD_PROC_COUNT; i++)
							{
								if (CommandProcessors[i]->processCommand(command, response))
								{
									sendResponseAsJson(client, response,false);
									break;
								}
							}
							command.free();
						}
						else
						{
							String fileName = isRequestedFile(_readString);
							Serial.println(String("File=") + fileName);
							if (SD.exists(fileName))
							{
								sendFile(client, fileName);
							}
						}
					}
					_readString = "";
					break;
				}
				if (c == '\n') {

					currentLineIsBlank = true;
				}
				else if (c != '\r') {

					currentLineIsBlank = false;
				}
			} // end if (client.available())
		} // end while (client.connected())
		delay(1);      // give the web browser time to receive the data
		client.stop(); // close the connection
	} // end if (client)
}



String WebService::isRequestedFile(String &request)
{
	String file;
	int indexHTTP = request.indexOf("HTTP");
	if (indexHTTP > -1 && request.startsWith("GET /"))
	{
		request = request.substring(4, indexHTTP);//remove GET
		request.trim();
		int indexEnd = request.indexOf("?");
		if (indexEnd > 0)
		{
			file = request.substring(0, indexEnd);
		}
		else
		{
			file = request.substring(0, indexEnd);
			if (file == "/") {
				file = "index.htm";
			}
		}
		return file;
	}
	return "";
};

void WebService::sendFile(EthernetClient &client, const String &fileName)
{
	Serial.println(String("sendFile=") + fileName);
	File myFile = SD.open(fileName);
	if (myFile) {

		if (!fileName.endsWith(".png"))
		{
			client.println("HTTP/1.1 200 OK");
			client.println("Content-Type: text/html");
			client.println("Connection: close");  // the connection will be closed after completion of the response
			client.println();
		}
		while (myFile.available()) {
			client.write(myFile.read());
		}
		myFile.close();
	}
	else
	{
		Serial.println("error opening " + fileName);
	}

};
void WebService::sendResponseAsJson(EthernetClient &client, const String &response, bool isHtml)
{
	if (response.length() > 0)
	{
		if (isHtml)
		{
			client.println("HTTP/1.1 200 OK");
			client.println("Content-Type: application/json; charset=utf-8");
			client.println("Connection: close");  // the connection will be closed after completion of the response
			client.println();
		}
		client.println(response);
	}
}

WebService webService;


