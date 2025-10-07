#include <M5CoreS3.h>
#include <M5UnitENV.h>

auto& Display = CoreS3.Display;

QMP6988 qmp6988;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(2);

  Wire.begin(/*SDA=*/2, /*SCL=*/1);

  // I2Cのアドレスを明示的に指定
  // 第三、第四引数はWireでも指定した　SDA/SCLだが省略はできない
  if (!qmp6988.begin(&Wire, 0x70, 2, 1)) {
    Display.setCursor(20, 20);
    Display.print("Pressure sensor init failed");
    while (true) delay(100);
  }
}

void loop() {
  CoreS3.update();

  if (!qmp6988.update()) {
    return;
  }

  float pressure = qmp6988.pressure;
  // PaからhPaに変換(1hPa = 100Pa)
  float pressure_hPa = pressure / 100.0;

  Display.setCursor(20, 20);
  Display.printf("Press: %.2f hPa", pressure_hPa);

  delay(1000);
}
