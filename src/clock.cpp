#include "clock.h"

RTClock::RTClock() {
  this->NTPch = new NTPtime("time.google.com");

  this->ntpTicker.attach_ms(30000, std::bind(&RTClock::updateNTPTime, this));
  this->timeTicker.attach_ms(1000, std::bind(&RTClock::updateTime, this));

  
}

RTClock::~RTClock() {

}

void RTClock::queryTime() {
  strDateTime dateTime = NTPch->getNTPtime(1.0, 1);;

  while(!dateTime.valid) {
    dateTime = NTPch->getNTPtime(1.0, 1);

    if(dateTime.valid){
      this->hours = dateTime.hour;
      this->minutes =  dateTime.minute;
      this->seconds = dateTime.second;

      this->receivedTimeOnce = true;
    }
  }
}

void RTClock::updateNTPTime() {
  strDateTime dateTime = NTPch->getNTPtime(1.0, 1);
  Serial.println("Updating");

  if(dateTime.valid){
    this->hours = dateTime.hour;
    this->minutes = dateTime.minute;
    this->seconds = dateTime.second;

    this->receivedTimeOnce = true;
  }
}

void RTClock::updateTime() {
  seconds++;

  if (seconds >= 60) {
    seconds = 0;
    minutes++;
  }

  if (minutes >= 60) {
    minutes = 0;
    hours++;
  }

  if (hours >= 24) {
    hours = 0;
  }
}