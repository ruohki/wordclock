#include "otaupdate.h"

OTAUpdate::OTAUpdate() {

}

bool OTAUpdate::checkForUpdate() {
  HTTPClient http;  //Object of class HTTPClient
  WiFiClient client;

  /* if (WiFi.status() == WL_CONNECTED) {
    if (http.begin(client, "http://jsonplaceholder.typicode.com/users/1")) {
     int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();

        Serial.println(payload);

        const size_t capacity = 255;
        DynamicJsonDocument doc(capacity);
        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.c_str());
          return false;
        }

        Serial.println(doc["name"].as<char*>());
        Serial.println(doc["username"].as<char*>());
        Serial.println(doc["email"].as<char*>());
        http.end();
        return true;
      }
    } */
  //}


/* 
  t_httpUpdate_return ret = ESPhttpUpdate.update("192.168.178.58", 5500, "/firmware.bin", );
  switch(ret) {
    case HTTP_UPDATE_FAILED:
        Serial.println("[update] Update failed.");
        break;
    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("[update] Update no Update.");
        break;
    case HTTP_UPDATE_OK:
        Serial.println("[update] Update ok."); // may not called we reboot the ESP
        break;
  } */
  return false;
}