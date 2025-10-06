#include <M5CoreS3.h>
#include "M5_UNIT_8SERVO.h"

auto& Display = CoreS3.Display;
M5_UNIT_8SERVO servos;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(2);

  Wire.begin(/*SDA=*/2, /*SCL=*/1, /*freq=*/100000);

  if (!servos.begin(&Wire, 0x25)) {
    Display.println("8SERVOS begin FAILED");
    while (true) delay(1000);
  }

  servos.setAllPinMode(SERVO_CTL_MODE);
}

void loop() {
  static int angle = 10;
  static int step  = 2;

  servos.setServoAngle(0, angle);

  Display.setCursor(20, 20);
  Display.printf("CH0 angle=%3d", angle);

  angle += step;
  if (angle >= 170 || angle <= 10) step = -step;

  CoreS3.update();
  delay(15);
}
