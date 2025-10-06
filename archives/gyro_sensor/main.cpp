#include <M5CoreS3.h>

auto& Display = CoreS3.Display;
auto& Imu = CoreS3.Imu;

struct GyroBias {
  float x;
  float y;
  float z;
};

GyroBias calibrate_gyro() {
  constexpr int CALIBRATION_SAMPLE_COUNT = 500;
  float sum_x = 0, sum_y = 0, sum_z = 0;

  for (int i = 0; i < CALIBRATION_SAMPLE_COUNT; ++i) {
    float gx, gy, gz;
    Imu.getGyro(&gx, &gy, &gz);
    sum_x += gx;
    sum_y += gy;
    sum_z += gz;
    delay(2);
  }

  return {
    sum_x / CALIBRATION_SAMPLE_COUNT,
    sum_y / CALIBRATION_SAMPLE_COUNT,
    sum_z / CALIBRATION_SAMPLE_COUNT
  };
}

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

  // バイアスの計算
  static GyroBias gyro_bias = calibrate_gyro();

  // 角速度（deg/s）の取得
  float gx, gy, gz;
  Imu.getGyro(&gx, &gy, &gz);

  // キャリブレーション(バイアス補正)
  gx -= gyro_bias.x;
  gy -= gyro_bias.y;
  gz -= gyro_bias.z;

  int x = 20;
  int y = 20;
  int line_height = 30;

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(x, y);
  Display.printf("X: %6.3f dps\n", gx);

  Display.setCursor(x, y + line_height);
  Display.printf("Y: %6.3f dps\n", gy);

  Display.setCursor(x, y + line_height * 2);
  Display.printf("Z: %6.3f dps\n", gz);

  delay(200);
}
