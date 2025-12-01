#include <M5CoreS3.h>
#include <Preferences.h>

auto& Display = CoreS3.Display;
Preferences prefs;

const char* KEY_NAME = "textdata";

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.setRotation(1);
  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(2);
  Display.setCursor(20, 20);
}

void loop() {
  // 名前空間 "storage" を開く
  // 第二引数で読み書き可能であることを指定
  prefs.begin("storage", false);

  // 読み出し
  String greet = prefs.getString("greet", "greet not found");
  Display.fillScreen(TFT_BLACK);
  Display.setCursor(20, 20);
  Display.println(greet);
  delay(1000);

  // 書き込み
  prefs.putString("greet", "hello, world!");

  // 読み出し
  greet = prefs.getString("greet", "greet not found");
  Display.fillScreen(TFT_BLACK);
  Display.setCursor(20, 20);
  Display.println(greet);
  delay(1000);

  // 削除
  prefs.remove("greet");

  prefs.end();
}
