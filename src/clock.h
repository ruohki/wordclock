#include <Arduino.h>
#include <Ticker.h>

#include <NTPtimeESP.h>

class RTClock {
  private:
    void updateNTPTime();
    void updateTime();
    
    Ticker ntpTicker;
    Ticker timeTicker;

    uint8_t hours = 0;
    uint8_t minutes = 0;
    uint8_t seconds = 0;

    bool receivedTimeOnce = false;

    NTPtime * NTPch; 

  public:
    RTClock();
    ~RTClock();
    
    int getHours() {
      return this->hours;
    }
    int getMinutes() {
      return this->minutes;
    }
    int getSeconds() {
      return this->seconds;
    }
    bool gotTimeOnce() {
      return this->receivedTimeOnce;
    }

    void queryTime();
    //void Tick();
};