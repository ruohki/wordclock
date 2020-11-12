#include <Arduino.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ArduinoJson.h>

class OTAUpdate {
  public:
    OTAUpdate();
    ~OTAUpdate();

    bool checkForUpdate();
};