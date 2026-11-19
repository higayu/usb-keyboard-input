# PicoUSBStorage
Pico 2 W / Pico SDK 2.3.1. 読み取り専用 FAT12 (64 KiB)、HELLO.TXT (UTF-8 BOM) を公開します。HIDは無効です。自動実行・自動コピーなし。
VS Code Pico extensionでフォルダを開き、Configure / Compile。あるいはSDK設定済み端末で `cmake -S . -B build -G Ninja`、`cmake --build build`。BOOTSELで build/PicoUSBStorage.uf2 をコピーします。
実機ビルドは未検証。USB VID/PIDは実験用で製品配布には適切な割当が必要です。
