#include <M5CoreS3.h>
#include <VL53L0X.h>

auto& Display = CoreS3.Display;

VL53L0X tofSensor;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  Wire.begin(/*SDA=*/2, /*SCL=*/1);

  if (!tofSensor.init()) {
    Display.setCursor(20, 20);
    Display.print("ToF init failed");
    while (true) delay(100);
  }

  // 測定のタイムアウトを設定（500ms）
  tofSensor.setTimeout(500);
}

void loop() {
  CoreS3.update();

  // 距離測定（mm単位）
  uint16_t distance = tofSensor.readRangeSingleMillimeters();

  Display.setCursor(20, 20);

  if (!tofSensor.timeoutOccurred()) {
    Display.printf("Distance: %d mm", distance);
  } else {
    Display.print("Timeout!");
  }

  delay(100);
}
