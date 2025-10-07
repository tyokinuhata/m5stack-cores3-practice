#include <M5CoreS3.h>
#include <Adafruit_SGP30.h>

auto& Display = CoreS3.Display;

Adafruit_SGP30 sgp;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  Wire.begin(/*SDA=*/2, /*SCL=*/1);

  if (!sgp.begin()) {
    Display.setCursor(20, 20);
    Display.print("SGP30 not found!");
    while (true) delay(100);
  }
}

void loop() {
  CoreS3.update();

  if (!sgp.IAQmeasure()) {
    Display.setCursor(20, 20);
    Display.print("Measurement failed!");
    delay(1000);
    return;
  }

  Display.setCursor(20, 20);
  Display.printf("TVOC: %5d ppb", sgp.TVOC);

  delay(100);
}
