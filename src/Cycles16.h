#ifndef Cycles16_h
#define Cycles16_h

#include "Arduino.h"

#ifndef __AVR__
#warning "This library has not been tested with your board."
#endif

#include "Arduino.h"

class Cycles16 {
private:
  static void startTimer2();
public:
  static void begin();
  static uint16_t now();
  static uint16_t elapsed(uint16_t, uint16_t);
  static uint16_t elapsedTillNow(uint16_t);
};

#endif
