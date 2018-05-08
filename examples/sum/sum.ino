#include <Cycles32.h>

void setup() {
  Cycles32::begin();
  Serial.begin(9600);
}

void loop() {
  static uint32_t sum = 0;
  static uint32_t lastNow = 0;
  uint32_t now = Cycles32::now();

  if (now < lastNow) {
    Serial.print(sum);
    Serial.print(" (maximum: ");
    Serial.print(UINT32_MAX);
    Serial.print(", now: ");
    Serial.print(now);
    Serial.print(", last now: ");
    Serial.print(lastNow);
    Serial.println(")");
    sum = now;
  } else {
    sum += now - lastNow;
  }

  lastNow = now;

  delayMicroseconds(100);
}
