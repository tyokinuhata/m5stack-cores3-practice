#include <M5CoreS3.h>

auto& Display = CoreS3.Display;
auto& Touch = CoreS3.Touch;

constexpr uint16_t PALETTE[] = {
  TFT_BLACK,
  TFT_WHITE,
  TFT_BLUE,
  TFT_RED,
  TFT_GREEN,
  TFT_YELLOW,
  TFT_CYAN,
  TFT_MAGENTA,
};
constexpr size_t PALETTE_LEN = sizeof(PALETTE) / sizeof(PALETTE[0]);

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(PALETTE[0]);
}

void loop() {
  static size_t color_index = 0;
  static bool last_pressed = false;

  CoreS3.update();

  auto t = Touch.getDetail();
  bool pressed = t.isPressed();

  if (pressed && !last_pressed) {
    color_index = (color_index + 1) % PALETTE_LEN;
    Display.fillScreen(PALETTE[color_index]);
  }
  last_pressed = pressed;

  // デバウンス
  delay(50);
}
