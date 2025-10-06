#include <M5CoreS3.h>

auto& Display = CoreS3.Display;
auto& Camera  = CoreS3.Camera;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  if (!Camera.begin()) {
    Display.setCursor(20, 20);
    Display.print("Camera init failed");
    while (true) delay(100);
  }

  if (Camera.sensor) {
    Camera.sensor->set_framesize(Camera.sensor, FRAMESIZE_QVGA);
  }

  Display.setCursor(20, 20);
  Display.print("Camera ready");
  delay(300);
  Display.fillScreen(TFT_BLACK);
}

void loop() {
  CoreS3.update();

  if (!Camera.get()) {
    delay(10);
    return;
  }

  Display.pushImage(
    0, 0,
    Display.width(),
    Display.height(),
    (uint16_t*)Camera.fb->buf
  );

  Camera.free();
  delay(10);
}
