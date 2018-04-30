#include <Cycles32.h>

void setup() {
  Cycles32::begin();
  Serial.begin(9600);
}

void loop() {
  static const unsigned long delayDuration = 1000; // ms
  static const float expectedCycles = float(F_CPU) * delayDuration / 1000;

  uint32_t cyclesAtStart = Cycles32::now();
  delay(delayDuration);
  uint32_t elapsedCycles = Cycles32::elapsedTillNow(cyclesAtStart);

  Serial.print("Elapsed cycles for delay of ");
  Serial.print(delayDuration);
  Serial.print(" ms duration: ");
  Serial.print(elapsedCycles);
  Serial.print(" (expected: ");
  Serial.print(expectedCycles);
  Serial.println(")");

  delay(500);
}
