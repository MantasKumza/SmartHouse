#include "MotionSensor.h"
#include "MotionSensor.h"
#include "motionSensor.h"
#include <EEPROM.h>
#include "BlinkControl.h"
#include <SD.h>
#include <SPI.h>
#include <EthernetServer.h>
#include <EthernetClient.h>
#include <Ethernet.h>


#include <Sodaq_DS3231.h>
#include <Wire.h>

#include "WebService.h"
#include "TimerControler.h"
#include "Command.h"
#include "LightSensor.h"
#include "OutdoorLightControl.h"
#include "CommandProcessor.h"
#include "Constants.h"

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
  rtc.begin();
  
  webService.CommandProcessors[0] = &outdoorLightControl;
  webService.CommandProcessors[1] = &lightSensor;
  webService.CommandProcessors[2] = &timerControler;

  outdoorLightControl.begin();
  outdoorLightControl.setupZone(PIN_12_IN_1, PIN_12_OUT_1, Terrace);
  outdoorLightControl.setupZone(PIN_12_IN_2, PIN_12_OUT_2, Summerhouse);
  outdoorLightControl.setupZone(PIN_12_IN_3, PIN_12_OUT_3, Fireplace);
  outdoorLightControl.setupZone(PIN_12_IN_4, PIN_12_OUT_4, DriveIn);
  lightSensor.setup(PIN_LIGHT_SENSOR_IN, PIN_LIGHT_SENSOR_OUT, 400);
  blinkControl.setup(PIN_BLINK_OUT);
  webService.begin(_ip, _dnsAndGateway);


  outdoorLightControl.printInfo();
  lightSensor.printInfo();
  timerControler.printInfo();
  
}

void loop()
{
	
  webService.listenForClient();
  outdoorLightControl.checkState();
  blinkControl.blink();
 
}
void printState()
{

}


