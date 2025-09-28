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

- VSCodeにPlatformIOの拡張がインストールされている前提
- エディタ下部の ✅️ でビルド
- エディタ下部の ➡️ で書き込み
- なお、書き込み時にはM5Stack本体のリセットボタンを2秒間長押しし、ダウンロードモードに移行しておく(LEDが光る)

## archivesディレクトリについて

- `archives` 配下にある `main.cpp` を実行したい場合、そのコードを `src/main.cpp` に配置する
