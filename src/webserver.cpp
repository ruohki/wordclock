#include "webserver.h"
#include "settings.h"
#include "stdlib_noniso.h"

Webserver::Webserver(Display* display)
{
  this->display = display;

  MDNS.addService("http", "tcp", 80);

  SPIFFS.begin();

  server->on("/heap", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(ESP.getFreeHeap()));
  });

  server->on("/color", HTTP_GET, [](AsyncWebServerRequest *request) {
    Settings* set = new Settings();
    
    request->send(200, "application/json",
      "{\"brightness\":" + String(set->Brightness()) +
      ",\"r\":" + String(set->Red()) +
      ",\"g\":" + String(set->Green()) +
      ",\"b\":" + String(set->Blue()) +
      "}"
    );
  });

  server->on("/color", HTTP_POST, [&](AsyncWebServerRequest *request) {
    if (request->hasArg("bri") && request->hasArg("r") && request->hasArg("g") && request->hasArg("b")) {
      String pBri = request->arg("bri");
      String pR = request->arg("r");
      String pG = request->arg("g");
      String pB = request->arg("b");
      
      Settings* set = new Settings();
      set->UpdateBrightness(pBri.toInt());
      set->UpdateColor(pR.toInt(), pG.toInt(), pB.toInt());

      this->display->reloadSettings();
      Serial.println("Setting color: r:" + pR + " g: " + pG + " b: " + pB + " brightness: " + pBri);
      AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "{\"status\":true}");
      request->send(response);
    } else {
      AsyncWebServerResponse *response = request->beginResponse(500, "application/json", "{\"status\":false}");
      request->send(response);
    }
  });

  server->on("/restart", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String("OK!"));
    ESP.restart();
  });

  server->on("/config", HTTP_GET, [&](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.html");
    
    request->send(response);
  });
  
  server->on("/config", HTTP_POST, [&](AsyncWebServerRequest *request) {
    if (request->hasArg("c") && request->hasArg("v")) {
      String pC = request->arg("c");
      String pV = request->arg("v");

      auto configElement = pC;
      auto configValue = pV;

      if (configElement == "color") {
        File file = SPIFFS.open("/" + configElement, "w");
        Serial.println(configValue.toInt());
        file.write(configValue.toInt());
        file.close();
      }
    }
    
    AsyncWebServerResponse *response = request->beginResponse(200, "application/json", "{\"status\":true}");
    request->send(response);
  });


  server->on("/update/ui", HTTP_POST, [&](AsyncWebServerRequest *request)  {
    AsyncWebServerResponse *response = request->beginResponse((Update.hasError())?500:200, "application/json", (Update.hasError())?"{\"status\":false}":"{\"status\":true}");
    response->addHeader("Connection", "close");
    response->addHeader("Access-Control-Allow-Origin", "*");
    request->send(response);
  }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {

    File file;
    if(!index){
      Serial.printf("UploadStart: %s\n", filename.c_str());
      file = SPIFFS.open("/index.html", "w");
    } else {
      file = SPIFFS.open("/index.html", "a");
    };

    file.write(data, len);
    
    file.close();
    if(final){
      Serial.printf("UploadEnd: %s, %u B\n", filename.c_str(), index+len);
    }

  });

  server->on("/update/firmware", HTTP_POST, [&](AsyncWebServerRequest *request) {
      // the request handler is triggered after the upload has finished... 
      // create the response, add header, and send response
      AsyncWebServerResponse *response = request->beginResponse((Update.hasError())?500:200, "application/json", (Update.hasError())?"{\"status\":false}":"{\"status\":true}");
      response->addHeader("Connection", "close");
      response->addHeader("Access-Control-Allow-Origin", "*");
      request->send(response);
      restartRequired = true;
  }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    //Upload handler chunks in data
    if (!index) {
      uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;      
      if (!Update.begin(maxSketchSpace)){ // Start with max available size
          Update.printError(Serial);   
      }
      Update.runAsync(true); // Tell the updaterClass to run in async mode
    }
    if (Update.write(data, len) != len) {
        Update.printError(Serial); 
    }

    if (final) { // if the final flag is set then this is the last frame of data
      if (Update.end(true)) { //true to set the size to the current progress

      }
    }
  });

  server->on("*", HTTP_GET,  [&](AsyncWebServerRequest *request) {
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.html");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  server->serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server->onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    if (!index)
      Serial.printf("BodyStart: %u\n", total);
    Serial.printf("%s", (const char *)data);
    if (index + len == total)
      Serial.printf("BodyEnd: %u\n", total);
  });

  server->onNotFound([](AsyncWebServerRequest *request) {
    Serial.printf("NOT_FOUND: ");
    if (request->method() == HTTP_GET)
      Serial.printf("GET");
    else if (request->method() == HTTP_POST)
      Serial.printf("POST");
    else if (request->method() == HTTP_DELETE)
      Serial.printf("DELETE");
    else if (request->method() == HTTP_PUT)
      Serial.printf("PUT");
    else if (request->method() == HTTP_PATCH)
      Serial.printf("PATCH");
    else if (request->method() == HTTP_HEAD)
      Serial.printf("HEAD");
    else if (request->method() == HTTP_OPTIONS)
      Serial.printf("OPTIONS");
    else
      Serial.printf("UNKNOWN");
    Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

    if (request->contentLength())
    {
      Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
      Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
    }

    int headers = request->headers();
    int i;
    for (i = 0; i < headers; i++)
    {
      AsyncWebHeader *h = request->getHeader(i);
      Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
    }

    int params = request->params();
    for (i = 0; i < params; i++)
    {
      AsyncWebParameter *p = request->getParam(i);
      if (p->isFile())
      {
        Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
      }
      else if (p->isPost())
      {
        Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
      else
      {
        Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }

    request->send(404);
  });

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  server->begin();
}

void Webserver::loop() {
  if(restartRequired){
    yield();
    delay(1000);
    yield();
    ESP.restart();
  }
}