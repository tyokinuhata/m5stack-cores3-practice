#include <M5CoreS3.h>
#include <Wire.h>
#include <M5_DLight.h>
#include <Adafruit_TCS34725.h>

auto& Display = CoreS3.Display;

constexpr uint8_t PAHUB_ADDR = 0x70;

constexpr uint8_t CH_AMBIENT_LIGHT = 0;
constexpr uint8_t CH_COLOR = 1;

M5_DLight dlight;

Adafruit_TCS34725 tcs(
  TCS34725_INTEGRATIONTIME_50MS,
  TCS34725_GAIN_4X
);

// PaHubのチャンネル切り替え
void selectPaHubChannel(uint8_t ch) {
  Wire.beginTransmission(PAHUB_ADDR);
  Wire.write(1 << ch);
  Wire.endTransmission();
}

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  Wire.begin(CoreS3.Ex_I2C.getSDA(), CoreS3.Ex_I2C.getSCL(), 400000);

  // 照度センサ 初期化
  selectPaHubChannel(CH_AMBIENT_LIGHT);
  dlight.begin(&Wire, CoreS3.Ex_I2C.getSDA(), CoreS3.Ex_I2C.getSCL());
  dlight.setMode(CONTINUOUSLY_H_RESOLUTION_MODE);

  // カラーセンサ初期化
  selectPaHubChannel(CH_COLOR);
  if (!tcs.begin(0x29, &Wire)) {
    Display.setCursor(20, 20);
    Display.print("TCS34725 Init Fail");
    while (true) delay(10);
  }
}

void loop() {
  CoreS3.update();

  // 照度センサ
  selectPaHubChannel(CH_AMBIENT_LIGHT);
  uint16_t lux = dlight.getLUX();

  // カラーセンサ
  selectPaHubChannel(CH_COLOR);
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

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(20, 20);
  Display.printf("Lux: %-5u", lux);

  Display.setCursor(20, 70);
  Display.printf("R: %3u", rn);
  Display.setCursor(20, 110);
  Display.printf("G: %3u", gn);
  Display.setCursor(20, 150);
  Display.printf("B: %3u", bn);

  delay(100);
}
