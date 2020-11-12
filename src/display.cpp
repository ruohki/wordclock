#include "display.h"
#include "FS.h"


Display::Display() {
  FastLED.addLeds<NEOPIXEL, PIN>(currentLeds, NUMPIXELS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
};

Display::~Display() {
  FastLED.clear();
}

void Display::reloadSettings() {
  Settings* set = new Settings();
  this->displayColor = CRGB(set->Red(), set->Green(), set->Blue());
  Serial.println("Updating color: r:" + String(set->Red()) + " g: " + String(set->Green()) + " b: " + String(set->Blue()) + " brightness: " + String(set->Brightness()));
  FastLED.setBrightness(set->Brightness());
}

void Display::setDefault() {
  for (auto i = 0; i < NUMPIXELS; i++) {
    targetLeds[i] = CRGB::Black;
  }

  for (int i = 0; i < size(DEFAULT_LIT_PIXEL); i++) {
    uint8_t b = pgm_read_byte(DEFAULT_LIT_PIXEL + i);
    targetLeds[b] = this->displayColor;
  }
}

void Display::printArray(const uint8_t * arr, int n) {
  for (auto i = 0; i < n; i++) {
    uint8_t b = pgm_read_byte(arr + i);
    targetLeds[b] = this->displayColor;
  }
}


void Display::instantCommitChanges() {
  for (int i = 0; i < NUMPIXELS; i++) {
    currentLeds[i] = targetLeds[i];
  }
  FastLED.show();
}

void Display::render(uint8_t speed) {
  for (int i = 0; i < NUMPIXELS; i++) {
    currentLeds[i] = blend(currentLeds[i], targetLeds[i], speed);
  }
  FastLED.show();
}

void Display::setTime(uint8_t hour, uint8_t minute) {
  bool nextHour = false;

  // Es ist
  setDefault();

  // Stundendots
  for (int i = 0; i < 4; i++) {
    uint8_t b = (NUMPIXELS - 1) - i;
    targetLeds[b] = (minute % 5) > i ? this->displayColor : offColor;
  }
  



  if (minute >= 5 && minute < 10) {
    printArray(MFUENF, size(MFUENF));
    printArray(NACH, size(NACH));
  } else if (minute >= 10 && minute < 15) {
    printArray(MZEHN, size(MZEHN));
    printArray(NACH, size(NACH));
  } else if (minute >= 15 && minute < 20) {
    printArray(VIERTEL, size(VIERTEL));
    nextHour = true;
  } else if (minute >= 20 && minute < 25) {
    printArray(ZWANZIG, size(ZWANZIG));
    printArray(NACH, size(NACH));
  } else if (minute >= 25 && minute < 30) {
    printArray(MFUENF, size(MFUENF));
    printArray(VOR, size(VOR));
    printArray(HALB, size(HALB));
    nextHour = true;
  } else if (minute >= 30 && minute < 35) {
    printArray(HALB, size(HALB));
    nextHour = true;
  } else if (minute >= 35 && minute < 40) {
    printArray(MFUENF, size(MFUENF));
    printArray(NACH, size(NACH));
    printArray(HALB, size(HALB));
    nextHour = true;
  } else if (minute >= 40 && minute < 45) {
    printArray(MZEHN, size(MZEHN));
    printArray(NACH, size(NACH));
    printArray(HALB, size(HALB));
    nextHour = true;
  } else if (minute >= 45 && minute < 50) {
    printArray(DREIVIERTEL, size(DREIVIERTEL));
    nextHour = true;
  } else if (minute >= 50 && minute < 55) {
    printArray(MZEHN, size(MZEHN));
    printArray(VOR, size(VOR));
    nextHour = true;
  } else if (minute >= 55 && minute < 60) {
    printArray(MFUENF, size(MFUENF));
    printArray(VOR, size(VOR));
    nextHour = true;
  }

  if (minute < 5) {
    printArray(UHR, size(UHR));
  }

  // Wir müssen aufgrund der Zeitansage die stunde um 1 anheben Halb 4 = 03:30
  if (nextHour) {
    hour++;
  }

  if (hour >= 12) {
    hour -= 12;
  }

  switch(hour) {
    case 1:
      if (minute >= 5) {
        printArray(EINS, size(EINS));
      } else {
        printArray(EIN, size(EIN));
      }
      break;
    case 2:
      printArray(ZWEI, size(ZWEI));
      break;
    case 3:
      printArray(DREI, size(DREI));
      break;
    case 4:
      printArray(VIER, size(VIER));
      break;
    case 5:
      printArray(FUENF, size(FUENF));
      break;
    case 6:
      printArray(SECHS, size(SECHS));
      break;
    case 7:
      printArray(SIEBEN, size(SIEBEN));
      break;
    case 8:
      printArray(ACHT, size(ACHT));
      break;
    case 9:
      printArray(NEUN, size(NEUN));
      break;
    case 10:
      printArray(ZEHN, size(ZEHN));
      break;
    case 11:
      printArray(ELF, size(ELF));
      break;
    case 0:
    case 12:
      printArray(ZWOELF, size(ZWOELF));
      break;
  }
}