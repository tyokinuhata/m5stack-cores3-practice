#include <M5CoreS3.h>

auto& Display = CoreS3.Display;

constexpr int PB_OUT = 9;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  pinMode(PB_OUT, OUTPUT);
}

void loop() {
  digitalWrite(PB_OUT, HIGH);
  delay(3000);

  digitalWrite(PB_OUT, LOW);
  delay(3000);
}
