#include <M5CoreS3.h>

auto& Display = CoreS3.Display;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);
  Display.setCursor(20, 20);
  Display.print("Speaker test");

  if (!CoreS3.Speaker.begin()) {
    Display.setCursor(20, 20);
    Display.print("Speaker init failed");
    while (true) delay(100);
  }

  CoreS3.Speaker.setVolume(120);
}

void loop() {
  CoreS3.update();

  // ドレミファソラシド（C4〜C5）
  int scale1[] = {262, 294, 330, 349, 392, 440, 494, 523};
  // ドシラソファミレド（C5〜C4）
  int scale2[] = {523, 494, 440, 392, 349, 330, 294, 262};

  // ドレミファソラシド（C4〜C5）
  for (int f: scale1) {
    CoreS3.Speaker.tone(f, 500);
    delay(500);
  }

  // ドシラソファミレド（C4〜C5）
  for (int f: scale2) {
    CoreS3.Speaker.tone(f, 500);
    delay(500);
  }
}
