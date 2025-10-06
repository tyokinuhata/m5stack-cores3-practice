#include <M5CoreS3.h>

auto& Display = CoreS3.Display;
auto& Ltr553 = CoreS3.Ltr553;

Ltr5xx_Init_Basic_Para ltr_cfg = LTR5XX_BASE_PARA_CONFIG_DEFAULT;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  ltr_cfg.als_gain = LTR5XX_ALS_GAIN_48X;

  if (!Ltr553.begin(&ltr_cfg)) {
    Display.setCursor(20, 20);
    Display.print("Ltr553 Init Fail");
    while (true) delay(10);
  }

  Ltr553.setAlsMode(LTR5XX_ALS_ACTIVE_MODE);
}

void loop() {
  CoreS3.update();

  uint16_t als = Ltr553.getAlsValue();

  Display.setCursor(20, 20);
  Display.printf("ALS: %-5u", als);

  delay(100);
}
