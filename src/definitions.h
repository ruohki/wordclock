#pragma once

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define MAJOR 0
#define MINOR 1

#define defaultColor CRGB::Red
#define offColor CRGB::Black

#define PIN            D4
#define NUMPIXELS      114

template<typename T, int sz>
int size(T(&)[sz])
{
    return sz;
}

static const uint8_t DEFAULT_LIT_PIXEL[] PROGMEM = {0, 1, 3, 4, 5};

static const uint8_t MFUENF[] PROGMEM = {7, 8, 9, 10};
static const uint8_t MZEHN[] PROGMEM = {18, 19, 20, 21};
static const uint8_t FUENFZEHN[] PROGMEM = {7, 8, 9, 10, 18, 19, 20, 21};
static const uint8_t ZWANZIG[] PROGMEM = {11, 12, 13, 14, 15, 16, 17};

static const uint8_t VIERTEL[] PROGMEM = { 26, 27, 28, 29, 30, 31, 32};
static const uint8_t HALB[] PROGMEM = {44, 45, 46, 47};
static const uint8_t DREIVIERTEL[] PROGMEM = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

static const uint8_t NACH[] PROGMEM = {41, 40, 39, 38};
static const uint8_t VOR[] PROGMEM = {37, 36, 35};

static const uint8_t EINS[] PROGMEM = {60, 61, 62, 63};
static const uint8_t EIN[] PROGMEM = {61, 62, 63};
static const uint8_t ZWEI[] PROGMEM = {62, 63, 64, 65};
static const uint8_t DREI[] PROGMEM = {67, 68, 69, 70};
static const uint8_t VIER[] PROGMEM = {80, 79, 78, 77};
static const uint8_t FUENF[] PROGMEM = {73, 74, 75, 76};
static const uint8_t SECHS[] PROGMEM = {104, 105, 106, 107, 108};
static const uint8_t SIEBEN[] PROGMEM = {60, 59, 58, 57, 56, 55};
static const uint8_t ACHT[] PROGMEM = {89, 90, 91, 92};
static const uint8_t NEUN[] PROGMEM = {81, 82, 83, 84};
static const uint8_t ZEHN[] PROGMEM = {93, 94, 95, 96};
static const uint8_t ELF[] PROGMEM = {85, 86, 87};
static const uint8_t ZWOELF[] PROGMEM = { 49, 50, 51, 52, 53};

static const uint8_t UHR[] PROGMEM = {99, 100, 101};

static const uint8_t WELCOME[] PROGMEM = {13, 15, 17, 18, 19, 25, 28, 29, 30, 35, 37, 40, 67, 69, 71, 74, 75, 80, 82, 84, 86, 90, 92, 96, 97};

#endif DEFINITIONS_H