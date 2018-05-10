#ifndef Cycles32_h
#define Cycles32_h

#include "Arduino.h"

#ifndef __AVR__
#warning "This library has not been tested with your board."
#endif

class Cycles32 {
private:
  static void startTimer1();
public:
  static void begin();
  static uint32_t now();
  static uint32_t elapsed(uint32_t, uint32_t);
  static uint32_t elapsedTillNow(uint32_t);
};

#endif
