#include <M5CoreS3.h>
#include <Wire.h>
#include <SparkFun_STHS34PF80_Arduino_Library.h>

auto& Display = CoreS3.Display;
STHS34PF80_I2C tmos;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  Wire.begin(/*SDA=*/2, /*SCL=*/1, /*freq=*/400000);

  if (!tmos.begin()) {
    Display.setCursor(20, 20);
    Display.print("STHS34PF80 init failed!");
    while (true) delay(100);
  }
}

void loop() {
  CoreS3.update();

  sths34pf80_tmos_drdy_status_t drdy{};
  tmos.getDataReady(&drdy);

  if (drdy.drdy != 1) {
    delay(100);
    return;
  }

  sths34pf80_tmos_func_status_t st{};
  tmos.getStatus(&st);

  int16_t presence = 0;
  tmos.getPresenceValue(&presence);

  float temp = 0.0f;
  tmos.getTemperatureData(&temp);

  Display.fillScreen(TFT_BLACK);

  Display.setCursor(20, 20);
  Display.printf("Presence: %d\n", presence);

  Display.setCursor(20, 60);
  Display.printf("Motion: %s\n", st.mot_flag ? "YES" : "NO");

  Display.setCursor(20, 100);
  Display.printf("Temp: %.2f C\n", temp);

  delay(200);
}
