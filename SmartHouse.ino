#include "Config.h"
#include "MotionSensor.h"
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
#include "MotionSensor.h"

String _serialLine;


IPAddress _ip(192, 168, 1, 178);
IPAddress _dnsAndGateway(192, 168, 1, 1);

void setup()
{
  //Serial.begin(9600);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}
  delay(1000);
 
 

 // rtc.begin();
  /*
  webService.CommandProcessors[0] = &outdoorLightControl;
  webService.CommandProcessors[1] = &lightSensor;
  webService.CommandProcessors[2] = &timerControler;
  */
 // setupOutdoorLightControl();
  
//  webService.begin(_ip, _dnsAndGateway);
 // checkPins(38, 40);
  //setupExternalOutPuts();

//  lightSensor.setup(PIN_LIGHT_SENSOR_IN, PIN_OUT_40, 400);
  blinkControl.setup(PIN_OUT_38);

 /* outdoorLightControl.printInfo();
  lightSensor.printInfo();
  timerControler.printInfo();*/

 

}


void setupOutdoorLightControl()
{
  outdoorLightControl.begin();

  outdoorLightControl.setupZone(Zone_TerraceDown, PIN_12_OUT_1);
  outdoorLightControl.setupZone(Zone_TerraceGround, PIN_12_OUT_2);
  outdoorLightControl.setupZone(Zone_ArborDown, PIN_12_OUT_3);
  outdoorLightControl.setupZone(Zone_ArborGround, PIN_12_OUT_4);
  outdoorLightControl.setupZone(Zone_ActivePlace, PIN_12_OUT_5);

  outdoorLightControl.setupZone(Zone_DriveIn, PIN_12_OUT_6);
  outdoorLightControl.setupZone(Zone_Waterfall, PIN_12_OUT_7);

  outdoorLightControl.setupMotionSensor(MotionSensor_Terrace, PIN_12_IN_1);
  outdoorLightControl.setupMotionSensor(MotionSensor_Arbor, PIN_12_IN_2);
  outdoorLightControl.setupMotionSensor(MotionSensor_ActivePlace, PIN_12_IN_3);
  outdoorLightControl.setupMotionSensor(MotionSensor_DriveIn, PIN_12_IN_4);
}

void loop()
{

 // webService.listenForClient();
//  outdoorLightControl.checkState();
  blinkControl.blink();

  //delay(1000);
}

void setupExternalOutPuts()
{
	for (int i = PIN_OUT_38; i <= PIN_OUT_52; i++)
		pinMode(i, OUTPUT);
}
void checkPins(int from, int to)
{
	for (int i = from; i <= to; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
		delay(100);

	}
}


