#include <M5CoreS3.h>
#include <Wire.h>

auto& Display = CoreS3.Display;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);
  Display.setCursor(20, 20);
  Display.println("I2C on Port.A");

  // Port.Aをスキャン
  Wire.begin(/*SDA=*/2, /*SCL=*/1, /*freq=*/400000);

  int found = 0;
  int y_pos = 60;

  for (uint8_t addr = 0x03; addr <= 0x77; addr++) {
    Wire.beginTransmission(addr);
    uint8_t err = Wire.endTransmission();

    if (err != 0) {
      continue;
    }

    Display.setCursor(20, y_pos);
    Display.printf("- 0x%02X", addr);
    found++;
    y_pos += 30;
    delay(10);
  }

  if (found == 0) {
    Display.setCursor(20, y_pos);
    Display.println("No I2C device found.");
  }
}

void loop() {
  delay(1000);
}
