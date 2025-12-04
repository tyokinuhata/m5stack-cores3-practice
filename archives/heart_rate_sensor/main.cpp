#include <M5CoreS3.h>
#include <Wire.h>
#include <MAX30100_PulseOximeter.h>

auto& Display = CoreS3.Display;

const uint8_t HEART_I2C_ADDR = 0x57;

PulseOximeter pox;

uint32_t lastUpdateMs = 0;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  if (!pox.begin()) {
    Display.setCursor(20, 20);
    Display.println("MAX30100 Init Fail");
    while (true) delay(10);
  }

  // IRとLEDの明るさ調整
  pox.setIRLedCurrent(MAX30100_LED_CURR_14_2MA);
}

void loop() {
  CoreS3.update();
  pox.update();

  float bpm  = pox.getHeartRate();
  float spo2 = pox.getSpO2();

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(20, 20);
  Display.printf("HR: %5.1f bpm", bpm);

  Display.setCursor(20, 60);
  Display.printf("SpO2: %5.1f %%", spo2);

  delay(100);
}
