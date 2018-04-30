#include "Cycles16.h"

static volatile uint8_t timer2OverflowCount = 0;

uint16_t Cycles16::now() {
  uint16_t c = timer2OverflowCount;
  c <<= 8;
  c += TCNT2;
  return c;
}

uint16_t Cycles16::elapsed(uint16_t cyclesAtStart, uint16_t cyclesAtEnd) {
  static const uint16_t maxCycles = 0xffff;
  if (cyclesAtEnd < cyclesAtStart) {
    return cyclesAtEnd + (maxCycles - cyclesAtStart);
  }
  return cyclesAtEnd - cyclesAtStart;
}

uint16_t Cycles16::elapsedTillNow(uint16_t cyclesAtStart) {
  return Cycles16::elapsed(cyclesAtStart, Cycles16::now());
}

ISR(TIMER2_OVF_vect) {
  timer2OverflowCount ++;
}

void Cycles16::startTimer2() {
  TCCR2A = 0; // normal operation
  TCCR2B = bit(CS20); // no prescaling
  OCR2A = 0;
  OCR2B = 0;
  TIMSK2 |= bit(TOIE2); // Timer/Counter2, Overflow Interrupt Enable
}

void Cycles16::begin() {
  startTimer2();
}
