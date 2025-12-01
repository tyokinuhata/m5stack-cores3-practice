#include <M5CoreS3.h>

auto& Display = CoreS3.Display;

// Port.Aに接続している場合はGPIO0が使用されるため、ピン番号は1
constexpr int KEY_PIN = 1;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  // ボタン未押下でHIGH、押下でLOW
  pinMode(KEY_PIN, INPUT_PULLUP);

  Display.setRotation(1);
  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(4);
  Display.setCursor(20, 20);

  Display.println("Waiting ...");
}

void loop() {
  int state = digitalRead(KEY_PIN);

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(20, 20);

  if (state == LOW) {
    Display.println("PRESSED");
  } else {
    Display.println("RELEASED");
  }

  delay(50);
}
