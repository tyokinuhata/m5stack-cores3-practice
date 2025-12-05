#include <M5CoreS3.h>
#include <Wire.h>
#include <M5_DLight.h>

auto& Display = CoreS3.Display;

// Ambient Light Unit(BH1750FVI)のセンサオブジェクト
M5_DLight dLight;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  // 初期化
  dLight.begin(&Wire, CoreS3.Ex_I2C.getSDA(), CoreS3.Ex_I2C.getSCL());
  // 測定モードの設定(標準的なモード。連続/分解能は1lx/測定速度は120ms)
  dLight.setMode(CONTINUOUSLY_H_RESOLUTION_MODE);
}

void loop() {
  CoreS3.update();

  // lx（ルクス）値の取得
  uint16_t lux = dLight.getLUX();

  Display.setCursor(20, 20);
  Display.printf("Lux: %-5u", lux);

  delay(100);
}
