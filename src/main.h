#include <Arduino.h>
//#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h> 
#include <EEPROM.h>

#include "definitions.h"
#include "display.h"
#include "clock.h"
#include "otaupdate.h"
#include "webserver.h"

Display * display = new Display();
RTClock * rtc = new RTClock();
OTAUpdate * ota = new OTAUpdate();
Webserver * webserver;

void loop();
void setup();