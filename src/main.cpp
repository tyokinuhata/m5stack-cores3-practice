#include <M5CoreS3.h>

auto& Display = M5.Display;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  Display.setRotation(1);
  Display.fillScreen(0x222222);
  Display.setTextColor(0xFFFFFF, 0x222222);
  Display.setTextSize(4);
  Display.setCursor(20, 20);
  Display.print("hello, world!");
}

void loop() {
  M5.update();
}
