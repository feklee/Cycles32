#include "Cycles32.h"
#include <util/atomic.h>

static volatile uint32_t timer1OverflowCount = 0;

uint32_t Cycles32::now() {
  uint32_t oc, c;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    // Atomic block is necessary to avoid interrupts from interfering with
    // TEMP register while reading 16 bit counter.
    c = TCNT1;
  }
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    oc = timer1OverflowCount;
  }
  return (oc << 16) + c;
}

uint32_t Cycles32::elapsed(uint32_t cyclesAtStart, uint32_t cyclesAtEnd) {
  static const uint32_t maxCycles = UINT32_MAX;
  if (cyclesAtEnd < cyclesAtStart) {
    return cyclesAtEnd + (maxCycles - cyclesAtStart);
  }
  return cyclesAtEnd - cyclesAtStart;
}

uint32_t Cycles32::elapsedTillNow(uint32_t cyclesAtStart) {
  return Cycles32::elapsed(cyclesAtStart, Cycles32::now());
}

ISR(TIMER1_OVF_vect) {
  timer1OverflowCount ++;
}

void Cycles32::startTimer1() {
  TCCR1A = 0; // normal operation
  TCCR1B = bit(CS10); // no prescaling
  OCR1A = 0;
  OCR1B = 0;
  TIMSK1 |= bit(TOIE1); // Timer/Counter 1, Overflow Interrupt Enable
}

void Cycles32::begin() {
  startTimer1();
}
