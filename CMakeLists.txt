# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)

set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# 対象ボード
set(PICO_BOARD pico2_w CACHE STRING "Board type")

# Pico SDKの読み込み
include(pico_sdk_import.cmake)

# プロジェクト設定
project(PicoUSBStorage C CXX ASM)

# Pico SDKの初期化
pico_sdk_init()

# ソースファイル
add_executable(PicoUSBStorage
    PicoUSBStorage.cpp
    usb_descriptors.c
    msc_disk.c
)

# プログラム情報
pico_set_program_name(PicoUSBStorage "PicoUSBStorage")
pico_set_program_version(PicoUSBStorage "0.1")

# シリアル通信設定
pico_enable_stdio_uart(PicoUSBStorage 0)
pico_enable_stdio_usb(PicoUSBStorage 0)

# 使用するライブラリ
target_link_libraries(PicoUSBStorage
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

# インクルードディレクトリ
target_include_directories(PicoUSBStorage PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# UF2などの出力ファイルを生成
pico_add_extra_outputs(PicoUSBStorage)
