# ESP_AT_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WiFiManager.svg?)](https://www.ardu-badge.com/ESP_AT_WiFiManager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP_AT_WiFiManager.svg)](https://github.com/khoih-prog/ESP_AT_WiFiManager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP_AT_WiFiManager.svg)](http://github.com/khoih-prog/ESP_AT_WiFiManager/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Release v1.3.1](#release-v131)
  * [Major Release v1.3.0](#major-release-v130)
  * [Major Release v1.2.0](#major-release-v120)
  * [Major Release v1.1.0](#major-release-v110)
  * [Release v1.0.3](#release-v103)
  * [Release v1.0.2](#release-v102)
  * [Release v1.0.1](#release-v101)
 
---
---

## Changelog

### Release v1.3.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Major Release v1.3.0

1. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).

### Major Release v1.2.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico)
2. Update examples with new features

### Major Release v1.1.0

1. Use new efficient [**FlashStorage_STM32** library](https://github.com/khoih-prog/FlashStorage_STM32). 
2. Add support to new **STM32 core v2.0.0** and STM32L5
3. Permit auto-connect without waiting for Config Portal if stored data is valid and WiFi test connection is OK.
4. Update examples with new features

### Release v1.0.3

1. Add support to all **STM32F/L/H/G/WB/MP1 (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.)**
2. Add support to **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
3. Add sample Packages_Patches for **STM32F/L/H/G/WB/MP1** (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8)
4. Add Packages_Patches for other boards.
5. Add instructions to use EspSerial/Serial1 on some **STM32F/L/H/G/WB/MP1** boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.)
6. Add Packages' Patches for Arduino SAMD21 to fix compiler error issue for **Nano-33-IoT, ZERO, MKR, etc.**

### Release v1.0.2

1. Add support to **ESP32-AT-command shield**.

### Release v1.0.1

1. Add support to **nRF52 (AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)**. Credentials to be saved **automatically in LittleFS**.
2. Improve support to **STM32F/L/H/G/WB/MP1**. Credentials to be saved **automatically in EEPROM**.
3. Drop support to **Teensy** boards.


