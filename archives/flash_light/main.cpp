#include <M5CoreS3.h>

constexpr int FLASH_ENABLE_PIN = 8;
constexpr int FLAST_CTRL_PIN = 9;

constexpr int PWM_CHANNEL    = 0;
constexpr int PWM_FREQ_HZ  = 5000;
constexpr int PWM_RESOLUTION = 8;

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  // AW3641ドライバICを有効化するための信号ピンを出力に設定
  pinMode(FLASH_ENABLE_PIN, OUTPUT);
  // LEDの明るさ・点灯を制御する信号ピンを出力に設定
  pinMode(FLAST_CTRL_PIN, OUTPUT);

  // AW3641ドライバICの電源を有効化
  digitalWrite(FLASH_ENABLE_PIN, HIGH);

  // どのチャンネルを何Hz、何段階の明るさで動かすかを指定
  ledcSetup(PWM_CHANNEL, PWM_FREQ_HZ, PWM_RESOLUTION);
  // チャンネルの出力先として FLASH_CTRL_PIN を割り当てる
  ledcAttachPin(FLAST_CTRL_PIN, PWM_CHANNEL);
}

void loop() {
  ledcWrite(PWM_CHANNEL, 255);
  delay(500);

  ledcWrite(PWM_CHANNEL, 0);
  delay(500);
}
