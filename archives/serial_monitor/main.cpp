#include <M5CoreS3.h>

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Serial.begin(115200);
  Serial.println("Ready.");
}

void loop() {
  Serial.printf("[%.1f s] Loop is running\n", millis() / 1000.0);
  delay(5000);
}
