#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

#include <Arduino.h>
#include <EEPROM.h>

#include "definitions.h"

struct SettingsStruct {
  byte red = 255;
  byte green = 0;
  byte blue = 0;
  byte brightness = 100;
};

class Settings {
  private:
    SettingsStruct settings;
    void Save() {
      EEPROM.put(0, this->settings);
      EEPROM.commit();
    }

  public:
    Settings() {
      EEPROM.get(0, this->settings);
    }

    void UpdateColor(byte red, byte green, byte blue) {
      this->settings.red = red;
      this->settings.green = green;
      this->settings.blue = blue;
      this->Save();
    }

    void UpdateBrightness(byte brightness) {
      this->settings.brightness = brightness;
      this->Save();
    }

    byte Red() {
      return this->settings.red;
    }
    byte Green() {
      return this->settings.green;
    }
    byte Blue() {
      return this->settings.blue;
    }
    byte Brightness() {
      return this->settings.brightness;
    }
};

#endif