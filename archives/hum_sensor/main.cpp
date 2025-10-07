#include <M5CoreS3.h>
#include <M5UnitENV.h>

auto& Display = CoreS3.Display;

SHT3X sht30;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  Wire.begin(/*SDA=*/2, /*SCL=*/1);

  // I2Cのアドレスを明示的に指定
  // 第三、第四引数はWireでも指定した　SDA/SCLだが省略はできない
  if (!sht30.begin(&Wire, 0x44, 2, 1)) {
    Display.setCursor(20, 20);
    Display.print("ENV III init failed");
    while (true) delay(100);
  }
}

void loop() {
  CoreS3.update();

  if (!sht30.update()) {
    return;
  }

  float humidity = sht30.humidity;

  Display.setCursor(20, 20);
  Display.printf("Hum: %.2f %%", humidity);

  delay(1000);
}
