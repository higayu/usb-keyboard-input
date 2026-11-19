# PicoUSBKeyboard
Pico 2 W / Pico SDK 2.3.1 / TinyUSB / C++17

所有・管理するWindows PCでのみ使用してください。接続後約5秒で Win+R、powershell、Enter を一度送信します。追加のコマンドは実行しません。Windowsはロック解除済み、入力モードは半角英数にしてください。画面状態によっては失敗します。

既存プロジェクトをバックアップし、同名ファイルを上書きします。VS CodeでCompileを実行し、build/PicoUSBKeyboard.uf2をBOOTSELモードのドライブにコピーします。既存の.vscode設定は保持してください。停止するにはUSBを抜いてください。再書き込みにはBOOTSELを使用します。

実機・SDKでのビルドは未検証です。USB VID/PIDは開発検証用の仮値であり製品配布用ではありません。
