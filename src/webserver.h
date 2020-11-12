#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <ArduinoJson.h>

#include "definitions.h"
#include "display.h"

class Webserver {
  private:
    AsyncWebServer * server = new AsyncWebServer(80);
    bool restartRequired = false;
    Display* display;

  public:
    Webserver(Display* display);

    ~Webserver();
    void loop();
    AsyncWebServer * getRawServer() {
      return server;
    }
};