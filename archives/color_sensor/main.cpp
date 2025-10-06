#include <M5CoreS3.h>
#include <Adafruit_TCS34725.h>

auto& Display = CoreS3.Display;

Adafruit_TCS34725 tcs(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  if (!tcs.begin(0x29, &Wire)) {
    Display.setCursor(20, 20);
    Display.print("TCS34725 Init Fail");
    while (true) delay(10);
  }
}

void loop() {
  CoreS3.update();

  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  uint8_t rn = 0, gn = 0, bn = 0;
  if (c > 0) {
    float rf = (float)r / (float)c;
    float gf = (float)g / (float)c;
    float bf = (float)b / (float)c;

    rn = (uint8_t)constrain(rf * 255.0f, 0.0f, 255.0f);
    gn = (uint8_t)constrain(gf * 255.0f, 0.0f, 255.0f);
    bn = (uint8_t)constrain(bf * 255.0f, 0.0f, 255.0f);
  }

  Display.setCursor(20, 20);   Display.printf("R: %3u", rn);
  Display.setCursor(20, 60);   Display.printf("G: %3u", gn);
  Display.setCursor(20, 100);  Display.printf("B: %3u", bn);

  delay(200);
}
