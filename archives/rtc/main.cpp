#include <M5CoreS3.h>

auto& Display = M5.Display;
auto& Rtc = CoreS3.Rtc;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  if (!Rtc.begin()) {
    Display.setCursor(20, 20);
    Display.print("RTC init failed");
    while (true) delay(100);
  }

  Rtc.setDateTime({ {2025, 10, 3}, {9, 0, 0} });

  Display.fillScreen(TFT_BLACK);
  Display.setTextSize(2);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
}

void loop() {
  auto dt = Rtc.getDateTime();

  Display.setCursor(20, 20);
  Display.printf("%04d/%02d/%02d %02d:%02d:%02d",
                 dt.date.year, dt.date.month, dt.date.date,
                 dt.time.hours, dt.time.minutes, dt.time.seconds);

  delay(1000);
}
