#include <M5CoreS3.h>
#include <WiFi.h>

auto& Display = CoreS3.Display;

const char* SSID = "XXXXXXXXXX";
const char* PASS = "XXXXXXXXXX";

bool connect_wifi() {
  const uint32_t timeout_ms = 20000;
  const int retries = 3;

  // NVSに接続情報を保存しない
  WiFi.persistent(false);
  // ステーションモード(≒子機モード)に設定
  WiFi.mode(WIFI_STA);
  // 省電力モードを無効化
  WiFi.setSleep(false);
  // 自動再接続を有効化
  WiFi.setAutoReconnect(true);

  for (int attempt = 1; attempt <= retries; attempt++) {
    // NVSをクリーンにして切断
    WiFi.disconnect(true, true);
    delay(150);

    WiFi.begin(SSID, PASS);

    uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - start) < timeout_ms) {
      delay(250);
      Display.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      return true;
    }

    WiFi.disconnect();
    delay(1000 + (attempt - 1) * 1000);
    Display.printf("\nRetrying WiFi ... (%d/%d)\n", attempt, retries);
  }
  return false;
}

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  Display.setRotation(1);
  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(2);
  Display.println("WiFi connecting ...");

  bool is_connected = connect_wifi();

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(0, 0);

  if (!is_connected) {
    Display.println("WiFi Failed");
    return;
  }

  Display.println("WiFi Connected!\n");
  Display.printf("SSID: %s\n", SSID);
  Display.printf("IP  : %s\n", WiFi.localIP().toString().c_str());
  // RSSI≒電波強度
  Display.printf("RSSI: %d dBm\n", WiFi.RSSI());
  Display.printf("MAC : %s\n", WiFi.macAddress().c_str());
}

void loop() {
  Display.fillScreen(TFT_BLACK);
  Display.setCursor(0, 0);

  if (WiFi.status() != WL_CONNECTED) {
    Display.println("WiFi Disconnected!");
    Display.printf("Status: %d\n", WiFi.status());
    Display.println("Auto-reconnecting ...");
    delay(2000);
    return;
  }

  Display.println("WiFi Connected!\n");
  Display.printf("SSID: %s\n", SSID);
  Display.printf("IP  : %s\n", WiFi.localIP().toString().c_str());
  Display.printf("RSSI: %d dBm\n", WiFi.RSSI());
  Display.printf("MAC : %s\n", WiFi.macAddress().c_str());

  delay(2000);
}
