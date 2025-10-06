#include <M5CoreS3.h>
#include <math.h>

auto& Display = CoreS3.Display;
auto& Imu = CoreS3.Imu;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  if (!Imu.begin()) {
    Display.setCursor(20, 20);
    Display.print("IMU init failed");
    while (true) delay(100);
  }
}

void loop() {
  CoreS3.update();

  float ax, ay, az;
  Imu.getAccel(&ax, &ay, &az);

  // ロール角(左右の角度)
  float roll  = atan2f(-ax, sqrtf(ay * ay + az * az)) * 180.0f / M_PI;
  // ピッチ角(前後の角度)
  float pitch = atan2f(ay, az) * 180.0f / M_PI;

  int x = 20;
  int y = 20;
  int line_height = 30;

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
