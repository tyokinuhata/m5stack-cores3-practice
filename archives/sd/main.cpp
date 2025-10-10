#include <M5CoreS3.h>
#include <FS.h>
#include <SD.h>

auto& Display = CoreS3.Display;

const char* FILE_PATH = "/test.txt";

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.setRotation(1);
  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(2);
  Display.setCursor(20, 20);

  if (!SD.begin(4)) {
    Display.println("SD mount failed.");
    while (true) delay(100);
  }

  {
    File f = SD.open(FILE_PATH, FILE_READ);
    if (!f) {
      Display.println("Open for read failed.");
      while (true) delay(100);
    }

    Display.printf("Read: %s\n\n", FILE_PATH);

    while (f.available()) {
      String line = f.readStringUntil('\n');
      Display.println(line);
    }
    f.close();
  }
}

void loop() {
  delay(1000);
}
