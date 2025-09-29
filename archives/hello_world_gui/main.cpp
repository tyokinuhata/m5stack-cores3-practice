#include <M5CoreS3.h>

auto& Display = M5.Display;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  const uint16_t bg = Display.color565(0x22, 0x22, 0x22);
  const uint16_t fg = Display.color565(0xFF, 0xFF, 0xFF);

  Display.setRotation(1);
  Display.fillScreen(bg);
  Display.setTextColor(fg, bg);
  Display.setTextSize(3);
  Display.setCursor(20, 20);
  Display.print("hello, world!");
}

void loop() {
  M5.update();
}
