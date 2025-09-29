#include <M5CoreS3.h>

auto& Display = M5.Display;
Ltr5xx_Init_Basic_Para ltr_cfg = LTR5XX_BASE_PARA_CONFIG_DEFAULT;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  const uint16_t bg = Display.color565(0x22, 0x22, 0x22);
  const uint16_t fg = Display.color565(0xFF, 0xFF, 0xFF);
  Display.fillScreen(bg);
  Display.setTextColor(fg, bg);
  Display.setTextSize(3);

  ltr_cfg.als_gain = LTR5XX_ALS_GAIN_48X;

  if (!CoreS3.Ltr553.begin(&ltr_cfg)) {
    Display.setCursor(20, 20);
    Display.print("Ltr553 Init Fail");
    while (1) delay(10);
  }

  CoreS3.Ltr553.setAlsMode(LTR5XX_ALS_ACTIVE_MODE);
}

void loop() {
  M5.update();

  uint16_t als = CoreS3.Ltr553.getAlsValue();

  Display.setCursor(20, 20);
  Display.printf("ALS: %-5u", als);

  delay(100);
}
