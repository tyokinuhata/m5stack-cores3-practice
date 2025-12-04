// M5CoreS3.h を使うと sensor_t 型が衝突し、コンパイルが通らないため、苦肉の策
#include <M5Unified.h>
#include <M5_IMU_PRO.h>
#include <math.h>

BMI270::BMI270 bmi270;

auto& Display = M5.Display;

constexpr uint8_t BMI270_SENSOR_ADDR = 0x68;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  M5.Ex_I2C.begin();
  bmi270.init(I2C_NUM_0, BMI270_SENSOR_ADDR);

  delay(500);
}

void loop() {
  M5.update();

  if (!bmi270.accelerationAvailable()) return;

  float ax, ay, az;
  bmi270.readAcceleration(ax, ay, az);

  float roll  = atan2f(-ax, sqrtf(ay * ay + az * az)) * 180.0f / M_PI;
  float pitch = atan2f(ay, az) * 180.0f / M_PI;

  const int x = 20;
  const int y = 20;
  const int line_height = 24;

  Display.fillScreen(TFT_BLACK);

  Display.setCursor(x, y);
  Display.printf("X: %6.3f\n", ax);

  Display.setCursor(x, y + line_height);
  Display.printf("Y: %6.3f\n", ay);

  Display.setCursor(x, y + line_height * 2);
  Display.printf("Z: %6.3f\n", az);

  Display.setCursor(x, y + line_height * 3);
  Display.printf("Roll : %6.3f\n", roll);

  Display.setCursor(x, y + line_height * 4);
  Display.printf("Pitch: %6.3f\n", pitch);

  delay(200);
}
