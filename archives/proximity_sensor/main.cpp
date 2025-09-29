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

  ltr_cfg.ps_led_pulse_freq   = LTR5XX_LED_PULSE_FREQ_40KHZ;
  ltr_cfg.ps_measurement_rate = LTR5XX_PS_MEASUREMENT_RATE_50MS;

  if (!CoreS3.Ltr553.begin(&ltr_cfg)) {
    Display.setCursor(20, 20);
    Display.print("Ltr553 Init Fail");
    while (true) delay(10);
  }

  CoreS3.Ltr553.setPsMode(LTR5XX_PS_ACTIVE_MODE);
}

void loop() {
  M5.update();

  uint16_t ps = CoreS3.Ltr553.getPsValue();

  Display.setCursor(20, 20);
  Display.printf("PS: %-5u", ps);

  delay(100);
}
