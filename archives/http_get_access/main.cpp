#include <M5CoreS3.h>
#include <WiFi.h>
#include <HTTPClient.h>

auto& Display = CoreS3.Display;

const char* SSID = "XXXXXXXXXX";
const char* PASS = "XXXXXXXXXX";

const char* URL = "https://example.com/";

bool connect_wifi() {
  const uint32_t timeout_ms = 20000;
  const int retries = 3;

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.setAutoReconnect(true);

  for (int attempt = 1; attempt <= retries; attempt++) {
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

struct HttpResult {
  int status;
  String body;
};

HttpResult http_get(const char* url) {
  HTTPClient http;
  HttpResult res{ -1, "" };

  if (!http.begin(url)) {
    return res;
  }
  http.setTimeout(5000);

  int code = http.GET();
  res.status = code;

  if (code > 0) {
    res.body = http.getString();
  } else {
    res.body = http.errorToString(code);
  }

  http.end();
  return res;
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
  Display.printf("RSSI: %d dBm\n", WiFi.RSSI());
  Display.printf("MAC : %s\n\n", WiFi.macAddress().c_str());

  Serial.begin(115200);
  Serial.println("Ready.");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Display.fillScreen(TFT_BLACK);
    Display.setCursor(0, 0);
    Display.println("WiFi Disconnected!");
    Display.printf("Status: %d\n", WiFi.status());
    Display.println("Auto-reconnecting ...");
    delay(2000);
    return;
  }

  HttpResult res = http_get(URL);

  Display.fillScreen(TFT_BLACK);
  Display.setCursor(0, 0);
  Display.printf("GET %s\n", URL);
  Display.printf("Status: %d\n", res.status);

  Serial.printf("GET %s\n", URL);
  Serial.printf("Status: %d\n", res.status);
  Serial.printf("Body: %s\n", res.body.c_str());

  delay(5000);
}
