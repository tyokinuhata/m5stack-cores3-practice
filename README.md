# m5stack-cores3-practice

## 接続の確認

```bash
# MacBookとM5StackをUSB Type-Cで接続後、接続されていることを確認
$ ls /dev/tty.*
...
crw-rw-rw- 9,10 root wheel 27 Sep 11:04 /dev/tty.usbmodem1101
...
```

## 書き込み

```bash
$ brew install platformio

# ビルド
$ pio run

# 書き込み
# 上手くいかない場合にはM5Stack本体のリセットボタンを2秒間長押しし、ダウンロードモードに移行すると(LEDが光る)上手くいく場合がある
$ pio run -t upload --upload-port /dev/cu.usbmodem1101
```

## archivesディレクトリについて

- `archives` ディレクトリ配下には過去の様々な実験スクリプトが配置されている
- 実行したい場合、そのコードを `src/main.cpp` に配置する
