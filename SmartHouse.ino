#include "test.h"
#include <SD.h>
#include <SPI.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Ethernet.h>


#include <Sodaq_DS3231.h>
#include <Wire.h>

#include "WebService.h"
#include "TimerContoler.h"
#include "Command.h"
#include "LightSensor.h"
#include "OutdoorLightControl.h"
#include "TimerContoler.h"


String _serialLine;

IPAddress _ip(192, 168, 1, 178);
IPAddress _dnsAndGateway(192, 168, 1, 1);

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  delay(100);

  outdoorLightControl.begin();
  outdoorLightControl.setupZone(30, 22, "Terrace");
  outdoorLightControl.setupZone(31, 23, "Summerhouse");
  outdoorLightControl.setupZone(32, 24, "Fireplace");
  outdoorLightControl.setupZone(33, 25, "DriveWay");

  outdoorLightControl.setupLightSensor(15, 900);

  DateTime time = rtc.now();
  Serial.println(String("Date:") + time.hour() + ":" + time.minute() + ":" + time.second());
  Serial.println(String("isDark=") + outdoorLightControl.isDark());

  webService.begin(_ip, _dnsAndGateway);

}

void loop()
{
  readLineFromSerial();
  webService.listenForClient();
 
  outdoorLightControl.checkState();

 
}
int readLineFromSerial() {
  char c;
  while ( Serial.available() != 0)
  {
    c = Serial.read();

    if (c != '\n')//if not work check Serial UI must set "newLine"
    {
      _serialLine += c;
    }
    else
    {
      
      _serialLine = "";
    }
  }
}

