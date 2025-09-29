#include <M5CoreS3.h>
#include <Adafruit_TCS34725.h>

auto& Display = M5.Display;

Adafruit_TCS34725 tcs(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  const uint16_t bg = Display.color565(0x22, 0x22, 0x22);
  const uint16_t fg = Display.color565(0xFF, 0xFF, 0xFF);
  Display.fillScreen(bg);
  Display.setTextColor(fg, bg);
  Display.setTextSize(3);

  if (!tcs.begin(0x29, &Wire)) {
    Display.setCursor(20, 20);
    Display.print("TCS34725 Init Fail");
    while (true) delay(10);
  }
}

void loop() {
  M5.update();

  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  const uint16_t bg = Display.color565(0x22, 0x22, 0x22);
  const uint16_t fg = Display.color565(0xFF, 0xFF, 0xFF);
  Display.setTextColor(fg, bg);

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
