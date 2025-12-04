#include <M5CoreS3.h>
#include <M5UNIT_NCIR2.h>

M5UNIT_NCIR2 ncir2;

auto& Display = CoreS3.Display;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  const int SDA_PIN = 2;
  const int SCL_PIN = 1;
  const uint8_t NCIR2_ADDR = 0x5A;

  if (!ncir2.begin(&Wire, SDA_PIN, SCL_PIN, NCIR2_ADDR)) {
    Display.setCursor(20, 20);
    Display.print("NCIR2 Init Fail");
    while (true) delay(10);
  }
}

void loop() {
  CoreS3.update();

  float raw = ncir2.getTempValue();
  float temp_c = raw / 100.0f;

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(20, 20);
  Display.printf("Temp: %.2f C", temp_c);

  delay(200);
}
