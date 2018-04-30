#include <Cycles16.h>

void setup() {
  Cycles16::begin();
  Serial.begin(9600);
}

void loop() {
  static const unsigned long delayDuration = 3; // ms
  static const float expectedCycles = float(F_CPU) * delayDuration / 1000;

  uint16_t cyclesAtStart = Cycles16::now();
  delay(delayDuration);
  uint16_t elapsedCycles = Cycles16::elapsedTillNow(cyclesAtStart);

  Serial.print("Elapsed cycles for delay of ");
  Serial.print(delayDuration);
  Serial.print(" ms duration: ");
  Serial.print(elapsedCycles);
  Serial.print(" (expected: ");
  Serial.print(expectedCycles);
  Serial.println(")");

  delay(500);
}
