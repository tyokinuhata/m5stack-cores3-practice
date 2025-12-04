#include <M5CoreS3.h>
#include "UNIT_SCALES.h"

UNIT_SCALES scales;

auto& Display = CoreS3.Display;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);
  Display.setCursor(0, 0);

  const int SDA_PIN = 2;
  const int SCL_PIN = 1;

  if (!scales.begin(&Wire, SDA_PIN, SCL_PIN, DEVICE_DEFAULT_ADDR)) {
      Display.setCursor(20, 20);
      Display.print("Mini Scales Init Fail");
      while (true) delay(10);
  }

  scales.setOffset();
}

void loop() {
  CoreS3.update();

  float weight = scales.getWeight();

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(20, 20);
  Display.printf("Weight: %.2f g\n", weight);

  delay(200);
}
