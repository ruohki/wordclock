#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include <Arduino.h>
#include <FastLed.h>

#include "settings.h"
#include "definitions.h"

class Display {
  
  private:

    CRGB currentLeds[NUMPIXELS];
    CRGB targetLeds[NUMPIXELS];

    void setDefault();
  
    CRGB displayColor = defaultColor;

  public:
    Display();
    ~Display();

    void reloadSettings();
    void instantCommitChanges();
    void printArray(const uint8_t * arr, int n);
    
    void render(uint8_t speed = 15);
    
    void setTime(uint8_t hour, uint8_t minute);
};

#endif