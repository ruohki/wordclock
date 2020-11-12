#include "main.h"
extern "C" {
  #include "user_interface.h"
}

#include "definitions.h"

void setup()
{
  wifi_set_sleep_type(LIGHT_SLEEP_T);
  
  Serial.begin(9600);
  EEPROM.begin(128);
  
  display->reloadSettings();
  display->printArray(WELCOME, size(WELCOME));
  display->instantCommitChanges();
  
  
  delay(1000);
  
  Serial.println("Hotspot");
  AsyncWebServer * captiveWebserver = new AsyncWebServer(80);
  DNSServer dns;

  AsyncWiFiManager wifiManager(captiveWebserver,&dns);
  wifiManager.autoConnect("wordclock");
  wifiManager.setDebugOutput(true);
  
  WiFi.hostname("wordclock");
  
  while ( WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  delete captiveWebserver;

  webserver = new Webserver(display);

  Serial.println("Query");
  rtc->queryTime();
}

void loop()
{
  if (rtc->gotTimeOnce()) {
    webserver->loop();
    display->setTime(rtc->getHours(), rtc->getMinutes());
    display->render(10);
  }
}