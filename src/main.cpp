#include <M5CoreS3.h>
#include <math.h>

auto& Display = M5.Display;

// 最小レベル(dBFS)
constexpr float DBFS_MIN = -70.0f;
// 最大レベル(dBFS)
constexpr float DBFS_MAX = 0.0f;
// EMA係数
constexpr float EMA_ALPHA = 0.2f;

// dBFSを0.0〜1.0の範囲にマップ
float dbfs_to_norm(float dbfs) {
  // クリッピング
  if (dbfs < DBFS_MIN) dbfs = DBFS_MIN;
  if (dbfs > DBFS_MAX) dbfs = DBFS_MAX;
  // 線形補間
  return (dbfs - DBFS_MIN) / (DBFS_MAX - DBFS_MIN);
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  Display.fillScreen(TFT_BLACK);
  Display.setTextColor(TFT_WHITE, TFT_BLACK);
  Display.setTextSize(3);

  if (!M5.Mic.begin()) {
    Display.setCursor(20, 20);
    Display.print("Mic init failed");
    while (true) delay(100);
  }
}

void loop() {
  M5.update();

  // PCM(Pulse Code Modulation, パルス符号変調)の取得
  static int16_t samples[1024];
  size_t n = M5.Mic.record(samples, 1024, 0);

  if (n == 0) {
    return;
  }

  double sumsq = 0.0;
  for (size_t i = 0; i < n; ++i) {
    // 正規化(-1.0〜+1.0の範囲に収める)
    float x = samples[i] / 32768.0f;
    // 二乗して正数にし、総和することで波のエネルギー量を算出
    sumsq += (double)x * x;
  }

  // RMS(Root Mean Square, 二乗平均平方根)
  // 二乗平均したものを平方根することで元のスケールに戻す
  float rms = (float)sqrt(sumsq / (double)n);

  // dBFS(デシベル)に変換
  // 1e-9fは極小値(10^-9)。RMSがゼロの場合に対数が計算できないことを防ぐ
  float dbfs  = 20.0f * log10f(rms + 1e-9f);

  // EMA(Exponential Moving Average, 指数移動平均)を用いた平準化
  static float smoothed_dbfs = DBFS_MIN;
  smoothed_dbfs = EMA_ALPHA * dbfs + (1.0f - EMA_ALPHA) * smoothed_dbfs;

  // レベルを高さに変換
  float norm = dbfs_to_norm(smoothed_dbfs);
  int h = Display.height();
  int w = Display.width();
  int bar_h = (int)(norm * h);

  Display.fillScreen(TFT_BLACK);
  Display.fillRect(0, h - bar_h, w, bar_h, TFT_BLUE);

  delay(33);
}
