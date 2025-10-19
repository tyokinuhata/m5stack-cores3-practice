#include <M5CoreS3.h>
#include <NimBLEDevice.h>

const char* UUID_SVC_RANDOM = "11111111-2222-3333-4444-555555555555";
const char* UUID_CHR_RANDOM = "11111111-2222-3333-4444-666666666666";

// プロファイル(GATT)はサーバ -> サービス -> キャラクタリスティックという階層構造
static NimBLEServer*         g_server     = nullptr;
static NimBLEService*        g_svc_random = nullptr;
static NimBLECharacteristic* g_chr_random = nullptr;

void setup_ble() {
  NimBLEDevice::init("ble-practice");
  NimBLEDevice::setSecurityAuth(false, false, false);

  g_server = NimBLEDevice::createServer();
  // 切断後、広告を再開する
  g_server->advertiseOnDisconnect(true);

  g_svc_random = g_server->createService(UUID_SVC_RANDOM);
  // 読み取り動作のみ有効
  g_chr_random = g_svc_random->createCharacteristic(
      UUID_CHR_RANDOM,
      NIMBLE_PROPERTY::READ
  );
  g_svc_random->start();

  auto adv = g_server->getAdvertising();
  adv->addServiceUUID(UUID_SVC_RANDOM);

  NimBLEAdvertisementData adv_data;
  adv_data.setName("ble-practice");
  adv_data.setCompleteServices(BLEUUID(UUID_SVC_RANDOM));
  adv->setAdvertisementData(adv_data);

  NimBLEAdvertisementData scan_data;
  scan_data.setName("ble-practice");
  scan_data.addServiceUUID(UUID_SVC_RANDOM);
  adv->setScanResponseData(scan_data);

  adv->start();
}

void setup() {
  auto cfg = M5.config();
  CoreS3.begin(cfg);

  randomSeed((uint32_t)esp_random());

  setup_ble();
}

void loop() {
  CoreS3.update();

  uint16_t value = (uint16_t)random(0, 10001);
  g_chr_random->setValue((uint8_t*)&value, sizeof(value));

  delay(100);
}
