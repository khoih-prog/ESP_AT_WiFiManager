# ESP_AT_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WiFiManager.svg?)](https://www.ardu-badge.com/ESP_AT_WiFiManager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP_AT_WiFiManager.svg)](https://github.com/khoih-prog/ESP_AT_WiFiManager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP_AT_WiFiManager.svg)](http://github.com/khoih-prog/ESP_AT_WiFiManager/issues)

---
---

## Table of Contents

* [Why do we need this ESP_AT_WiFiManager library](#why-do-we-need-this-esp_at_wifimanager-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](#changelog)
  * [Major Release v1.2.0](#major-release-v120)
  * [Major Release v1.1.0](#major-release-v110)
  * [Release v1.0.3](#release-v103)
  * [Release v1.0.2](#release-v102)
  * [Release v1.0.1](#release-v101)
* [Prerequisites](#prerequisites)
* [Important Notes about AT Firmwares](#important-notes-about-at-firmwares)
  * [1. Firmwares tested OK with ESP8266 AT shields](#1-firmwares-tested-ok-with-esp8266-at-shields)
  * [2. Firmwares tested OK with ESP32 AT shields](#2-firmwares-tested-ok-with-esp32-at-shields)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1 For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2 For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards](#8-for-rp2040-based-boards) 
* [How It Works](#how-it-works)
* [How to use](#how-to-use)
  * [1. Basic usage](#1-basic-usage)
  * [2. To open Config Portal](#2-to-open-config-portal)
  * [3. To use different AP WiFi Channel](#3-to-use-different-ap-wifi-channel)
  * [4. To use different static AP IP from default](#4-to-use-different-static-ap-ip-from-default)
  * [5. To use default AP SSID ESP_AT_XXXXXX](#5-to-use-default-ap-ssid-esp_at_xxxxxx)
  * [6. To use personalized AP SSID and Password](#6-to-use-personalized-ap-ssid-and-password)
* [Examples](#examples)
  * [ 1. ConfigOnSwitch](examples/ConfigOnSwitch)
  * [ 2. ConfigOnStartup](examples/ConfigOnStartup) 
  * [ 3. AutoConnect](examples/AutoConnect)
  * [ 4. AutoConnectWithFeedback](examples/AutoConnectWithFeedback)
* [So, how it works?](#so-how-it-works)
* [Documentation](#documentation)
  * [1. Password protect the configuration Access Point](#1-password-protect-the-configuration-access-point)
  * [2. Configuration Portal Timeout](#2-configuration-portal-timeout)
* [Custom Configuration](#custom-configuration)
  * [1. Custom Parameters](#1-custom-parameters)
  * [2. Custom IP Configuration](#2-custom-ip-configuration)
  * [3. Custom Access Point IP Configuration](#3-custom-access-point-ip-configuration)
  * [4. Custom Station (client) Static IP Configuration](#4-custom-station-client-static-ip-configuration)
  * [5. Custom HTML, CSS, Javascript](#5-custom-html-css-javascript)
    * [5.1 Inject custom head element](#51-inject-custom-head-element)
    * [5.2 Inject a custom bit of html in the configuration form](#52-inject-a-custom-bit-of-html-in-the-configuration-form)
    * [5.3 Inject a custom bit of html in a configuration form element](#53-inject-a-custom-bit-of-html-in-a-configuration-form-element)
  * [6. Filter Networks](#6-filter-networks)
* [Example ConfigOnSwitch](#example-configonswitch)
  * [1. File ConfigOnSwitch.ino](#1-file-configonswitchino)
  * [2. File defines.h](#2-file-definesh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ConfigOnSwitch on Adafruit Itsy-Bitsy nRF52840 with ESP8266-AT shield](#1-configonswitch-on-adafruit-itsy-bitsy-nrf52840-with-esp8266-at-shield)
    * [1.1 Enter Config Portal](#11-enter-config-portal)
    * [1.2 Click `Save`](#12-click-save)
  * [2. ConfigOnStartup on SAM-DUE with ESP32-AT shield](#2-configonstartup-on-sam-due-with-esp32-at-shield)
  * [3. ConfigOnStartup on STM32 Nucleo-144 NUCLEO_F767ZI with ESP8266-AT shield](#3-configonstartup-on-stm32-nucleo-144-nucleo_f767zi-with-esp8266-at-shield)
  * [4. ConfigOnStartup on Seeeduino SEEED_XIAO_M0 with ESP8266-AT shield](#4-configonstartup-on-seeeduino-seeed_xiao_m0-with-esp8266-at-shield)
  * [5. ConfigOnStartup on STM32 Nucleo-144 NUCLEO_F767ZI with ESP8266-AT shield  with invalid data](#5-configonstartup-on-stm32-nucleo-144-nucleo_f767zi-with-esp8266-at-shield-with-invalid-data)
    * [5.1 Data OK => No Config Portal](#51-data-ok--no-config-portal)
    * [5.2 Valid Data but no connection => Config Portal](#52-valid-data-but-no-connection--config-Portal)
  * [6. ConfigOnSwitch on RASPBERRY_PI_PICO with ESP8266-AT shield](#6-configonswitch-on-raspberry_pi_pico-with-esp8266-at-shield)
    * [6.1 No Config Data => Config Portal](#61-no-config-data--config-portal)
    * [6.2 Forced Config => Config Portal](#62-forced-config--config-portal)
    * [6.3 Data Saved => Connect WiFi](#63-data-saved--connect-wifi)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Releases](#releases)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [ESP_AT_WiFiManager library](https://github.com/khoih-prog/ESP_AT_WiFiManager)

#### Features

This [**ESP_AT_WiFiManager library**](https://github.com/khoih-prog/ESP_AT_WiFiManager) is based on, modified, bug-fixed and improved from:

1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)
3. [`Khoi Hoang's ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)

to support **nRF52, SAM DUE, SAMD, STM32F/L/H/G/WB/MP1, RASPBERRY_PI_PICO, etc. boards using ESP8266/ESP32-AT-command shields.**

The **RP2040-based boards, such as RASPBERRY_PI_PICO**, are currently supported using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico). The support to [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) will be added in the future.

The AVR-family boards (Mega, UNO, Nano, etc.) are **not supported** as they don't have enough memory to run Config Portal WebServer.

This is a Credentials / WiFi Connection Manager with fallback web configuration portal.

The web configuration portal, served from the `ESP8266/ESP32-AT-command shields` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

You can also specify static AP and STA IP. Config Portal will be auto-adjusted to match the number of dynamic custom parameters. Credentials are saved in EEPROM, [`FlashStorage_SAMD`](https://github.com/khoih-prog/FlashStorage_SAMD), [`FlashStorage_STM32`](https://github.com/khoih-prog/FlashStorage_STM32), [`DueFlashStorage`](https://github.com/sebnil/DueFlashStorage) or nRF52/RP2040 LittleFS.

---

#### Currently Supported Boards

This [**ESP_AT_WiFiManager** library](https://github.com/khoih-prog/ESP_AT_WiFiManager) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAM DUE**
 
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 
 6. **STM32F/L/H/G/WB/MP1 boards (with 64+K Flash)**

- Nucleo-144
- Nucleo-64
- Discovery
- Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
- STM32L0, STM32L1, STM32L4, **STM32L5**
- STM32G0, STM32G4
- STM32H7
- STM32WB
- STM32MP1
- LoRa boards
- 3-D printer boards
- Generic Flight Controllers
- Midatronics boards
 
 7. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico). 
 
---
---

## Changelog

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


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino AVR core 1.8.3+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Arduino Core for STM32 v2.0.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.). [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 4. [`Teensy core 1.53+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) boards
 5. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 6. [`Arduino SAMD core 1.8.11+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 7. [`Adafruit SAMD core 1.6.8+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 8. [`Seeeduino SAMD core 1.8.1+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 9. [`Adafruit nRF52 v0.21.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
10. [`Earle Philhower's arduino-pico core v1.2.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)  
11. [`ESP8266_AT_WebServer library v1.2.0+`](https://github.com/khoih-prog/ESP8266_AT_WebServer) to be able to support ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)
12. [`FlashStorage_SAMD library v1.1.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases/latest). Or [`Platform.io FlashStorage_SAMD library v1.0.0+`](https://platformio.org/lib/show/11242/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
13. [`FlashStorage_STM32 library v1.1.0+`](https://github.com/khoih-prog/FlashStorage_STM32) for STM32F/L/H/G/WB/MP1 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32)
14. [`DueFlashStorage library v1.0.0+`](https://github.com/sebnil/DueFlashStorage) for SAM DUE. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DueFlashStorage.svg?)](https://www.ardu-badge.com/DueFlashStorage)
15. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52 boards.
16. [`Ai-Thinker AT Firmware v1.5.4`](AT_Firmwares/At_firmware_bin1.54.zip) or [`AT Firmware v1.7.4.0`](AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip) for ESP8266-AT shields.
17. [`AT version_2.1.0.0_dev`](AT_Firmwares/AT_version_2.1.0.0_dev.zip) for ESP32-AT shields.
18. `AT version_1.1.4` for WIS600-01S and W600-AT WiFi shields.

---

### Important Notes about AT Firmwares

### 1. Firmwares tested OK with ESP8266 AT shields

  - [`Ai-Thinker AT Firmware v1.5.4`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/At_firmware_bin1.54.zip)
  
    ```
    AT version:1.1.0.0(May 11 2016 18:09:56)
    SDK version:1.5.4(baaeaebb)
    Ai-Thinker Technology Co. Ltd.
    Jun 13 2016 11:29:20
    ```
  - [`AT Firmware v1.7.4.0`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip)
  
    ```
    AT version:1.7.4.0(May 11 2020 19:13:04)
    SDK version:3.0.4(9532ceb)
    compile time:May 27 2020 10:12:17
    Bin version(Wroom 02):1.7.4
    ```
    
  - [`WIS600-01S`](https://www.aliexpress.com/item/32956707239.html) and [`W600`](https://www.seeedstudio.com/w600.html) using either ESP8266 or ESP32-AT commands and stock firmware
  
    ```
    AT version:1.1.4(Dec 05 2018 11:06:45)
    SDK version:3.0.0
    Dec 05 2018 11:06:45
    ```
  
  
### 2. Firmwares tested OK with ESP32 AT shields

  - [`AT version_2.1.0.0_dev`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_version_2.1.0.0_dev.zip)
    
    ```
    AT version:2.1.0.0-dev(4f6b92c - Jun 10 2020 10:36:54)
    SDK version:v4.0.1-193-ge7ac221b4
    compile time(b85a8df):Jun 18 2020 14:00:59
    Bin version:2.0.0(WROOM-32)
    ```
    
    See instructions at [AT Command Core](https://github.com/espressif/esp-at) and [ESP_AT_Get_Started](https://github.com/espressif/esp-at/blob/master/docs/en/get-started/ESP_AT_Get_Started.md)
  
3. Upload [`AT Firmware v1.7.4.0`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip) bin files to correct locations as follows:

```
# BOOT MODE

### Flash size 8Mbit: 512KB+512KB
    boot_v1.2+.bin              0x00000
    user1.1024.new.2.bin        0x01000
    esp_init_data_default.bin   0xfc000
    blank.bin                   0x7e000 & 0xfe000


### Flash size 16Mbit-C1: 1024KB+1024KB
    boot_v1.2+.bin              0x00000
    user1.2048.new.5.bin        0x01000
    esp_init_data_default.bin   0x1fc000
    blank.bin                   0xfe000 & 0x1fe000
```

4. Test before using different AT-Firmware Version at your own risks. Just use any simple example to verify if the AT-firmware is OK.
5. Compatible AT-Firmare version will be updated. Check for all supported AT Firmwares and download them from [AT_Firmwares](https://github.com/khoih-prog/ESP8266_AT_WebServer/tree/master/AT_Firmwares).
6. Support to ESP32-AT-command shields will be added by using new library [ESP_AT_Lib](https://github.com/khoih-prog/ESP_AT_Lib) to replace [Blynk's BlynkESP8266_Lib](https://github.com/blynkkk/blynk-library/releases/Blynk_Release_v0.6.1.zip).

---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `ESP_AT_WiFiManager`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WiFiManager.svg?)](https://www.ardu-badge.com/ESP_AT_WiFiManager) for more detailed instructions.

### Manual Install

1. Navigate to [ESP_AT_WiFiManager](https://github.com/khoih-prog/ESP_AT_WiFiManager) page.
2. Download the latest release `ESP_AT_WiFiManager-master.zip`.
3. Extract the zip file to `ESP_AT_WiFiManager-master` directory 
4. Copy whole 
  - `ESP_AT_WiFiManager-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**ESP_AT_WiFiManager** library](https://platformio.org/lib/show/7136/ESP_AT_WiFiManager) by using [Library Manager](https://platformio.org/lib/show/7136/ESP_AT_WiFiManager/installation). Search for **ESP_AT_WiFiManager** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 0.21.0](Packages_Patches/adafruit/hardware/nrf52/0.21.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0). 

Supposing the Adafruit nRF52 version is 0.21.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/0.21.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.13/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.13. These files must be copied into the directory:

- `./arduino-1.8.13/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.13/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.10](Packages_Patches/arduino/hardware/samd/1.8.10) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.10).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.11. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.11/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.8) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.8). 

Supposing the Adafruit SAMD core version is 1.6.8. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.8/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.8.1) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1). 

Supposing the Seeeduino SAMD core version is 1.8.1. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/1.9.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/1.9.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`


#### 8. For RP2040-based boards
 
 ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards***, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.2.1) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.2.1). 

Supposing the rp2040 core version is 1.2.1. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.2.1/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

---
---

## How It Works

- The [ConfigOnSwitch](examples/ConfigOnSwitch) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of ConfigOnSwitch is that a new `ESP8266/ESP32-AT shield` will start a WiFi configuration portal when powered up and save the configuration data in host's non-volatile memory. Thereafter, the configuration portal will only be started again if a button is pushed on the host board.
- Using any WiFi enabled device with a browser (computer, phone, tablet) connect to the newly created AP and type in the AP IP address (default 192.168.4.1).
- Choose one of the 3 best APs scanned, enter password, click `Save`.
- `ESP8266/ESP32-AT shield` will try to connect. If successful, the dynamic DHCP or configured static IP address will be displayed in the configuration portal. 
- The `ESP8266/ESP32-AT shield` WiFi Config Portal network and Web Server will shutdown to return control to the sketch code.

---
---

### How to use

#### 1. Basic usage

- Include in your sketch

```cpp

// Select depending on board
#define EspSerial Serial1

// Must be before #include <ESP_AT_WiFiManager.h>
// To store Credentials / WiFi Data
#define EEPROM_START        0

#include <ESP_AT_WiFiManager.h>              //https://github.com/khoih-prog/ESP_AT_WiFiManager

// Your Board <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

String ssid = "ESP_AT_" + String(0x1ABCDEF, HEX);
const char* password = "ESP_AT_PW";

IPAddress staticAP_IP = IPAddress(192,168,100,1);

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;

// Onboard LED I/O pin on board
const int LOCAL_PIN_LED = 13; // Pin 13, Controls the onboard LED.

#define LED_ON    HIGH
#define LED_OFF   LOW
```

#### 2. To open Config Portal

- When you want to open a config portal, just add

```cpp
ESP_AT_WiFiManager ESP_AT_wiFiManager;
```

#### 3. To use different AP WiFi Channel

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs, call 
```cpp
ESP_AT_wiFiManager.setAPChannel(newChannel);
```

- To use random AP WiFi Channel to avoid conflict with other WiFi APs : 

```cpp
ESP_AT_WiFiManager->setAPChannel(0);
```

#### 4. To use different static AP IP from default

- To use static IP (not the default dynamically allocated DHCP IP) from the network to be connected, call 
```cpp
ESP_AT_wiFiManager.setSTAStaticIPConfig(IPAddress(xxx,xxx,xxx,xxx));
```

- To use different static AP IP (not use default `192.168.4.1`), call 
```cpp
ESP_AT_wiFiManager.setAPStaticIPConfig(IPAddress(xxx,xxx,xxx,xxx));
```

#### 5. To use default AP SSID ESP_AT_XXXXXX

- To use default AP SSID `ESP_AT_XXXXXX`, call 

```cpp
ESP_AT_wiFiManager.startConfigPortal()
```

#### 6. To use personalized AP SSID and Password

- To use personalized SSID /  Password, call

```cpp
ESP_AT_wiFiManager.startConfigPortal((const char *) ssid.c_str(), password);
```

While in AP mode, connect to it using its `SSID` (ESP_AT_XXXXXX) / `Password` ("ESP_AT_PW"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then save. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


Once Credentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.

---
---

### Examples: 

1. [ConfigOnSwitch](examples/ConfigOnSwitch)
2. [ConfigOnStartup](examples/ConfigOnStartup) 
3. [AutoConnect](examples/AutoConnect)
4. [AutoConnectWithFeedback](examples/AutoConnectWithFeedback)
 
 
---
---

## So, how it works?

In `Configuration Portal Mode`, it starts an AP called `ESP_AT_XXXXXX`. Connect to it using the `configurable password` you can define in the code. For example, `ESP_AT_PW` (see examples):

```cpp
// SSID and PW for Config Portal
String ssid = "ESP_AT_" + String(0x1ABCDEF, HEX);
const char* password = "ESP_AT_PW";
```
After you connected, please, go to http://192.168.4.1 or newly configured AP IP, you'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/Images/Main.png">
</p>

Select `Information` to enter the Info page where the board info will be shown

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/Images/Info.png">
</p>

Select `Configuration` to enter this page where you can select an AP and specify its WiFi Credentials

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/Images/Configuration.png">
</p>

Enter your credentials, then click `Save`. The WiFi Credentials will be saved and the board connect to the selected WiFi AP.

If you're already connected to a listed WiFi AP and don't want to change anything, just select `Exit` from the `Main` page to reboot the board and connect to the previously-stored AP. The WiFi Credentials are still intact.

---
---

### Documentation

#### 1. Password protect the configuration Access Point

You can password protect the configuration AP.  Simply add an SSID as the first parameter and the password as a second parameter to `startConfigPortal` as follows:

```cpp
ESP_AT_wiFiManager.startConfigPortal(SSID , password);
```

Use Password having 8+ characters.

The guidelines are that a wifi password must consist of 8 to 63 ASCII-encoded characters in the range of 32 to 126 (decimal)


#### 2. Configuration Portal Timeout

You can set a timeout(in seconds) so that `ESP8266/ESP32-AT shield` doesn't hang waiting to be configured for ever. 

```cpp
ESP_AT_WiFiManager.setConfigPortalTimeout(60);
```

which will wait 1 minutes (60 seconds). 

When the time passes, the startConfigPortal function will return and continue the sketch, unless you're accessing the Config Portal. In this case, the `startConfigPortal` function will stay until you save config data or exit the Config Portal.

---

### Custom Configuration

#### 1. Custom Parameters

Many applications need configuration parameters like `MQTT host and port`, [Blynk](http://www.blynk.cc) or [emoncms](http://emoncms.org) tokens, etc. While it is possible to use `ESP_AT_WiFiManager` to collect additional parameters it is better to read these parameters from a web service once `ESP_AT_WiFiManager` has been used to connect to the internet. This makes `ESP_AT_WiFiManager` simple to code and use, parameters can be edited on a regular web server and can be changed remotely after deployment.


#### 2. Custom IP Configuration

You can set a custom IP for both AP (access point, config mode) and STA (station mode, client mode, normal project state)

#### 3. Custom Access Point IP Configuration

This will set your captive portal to a specific IP should you need/want such a feature. Add the following snippet before `startConfigPortal()`
```cpp
// Default AP IP is 192.168.4.1. Uncomment to use different AP IP
ESP_AT_wiFiManager.setAPStaticIPConfig(IPAddress(192,168,100,1));
```

#### 4. Custom Station (client) Static IP Configuration

This will use the specified IP configuration instead of using DHCP in station mode.
```cpp
// Set static STA IP
ESP_AT_wiFiManager.setSTAStaticIPConfig(IPAddress(192,168,2,114));
```

#### 5. Custom HTML, CSS, Javascript

There are various ways in which you can inject custom HTML, CSS or Javascript into the configuration portal.

The options are:

##### 5.1 Inject custom head element

You can use this to any html bit to the head of the configuration portal. If you add a `<style>` element, bare in mind it overwrites the included css, not replaces.

```cpp
ESP_AT_wiFiManager.setCustomHeadElement("<style>html{filter: invert(100%); -webkit-filter: invert(100%);}</style>");
```

##### 5.2 Inject a custom bit of html in the configuration form

```cpp
ESP_AT_WMParameter custom_text("<p>This is just a text paragraph</p>");
ESP_AT_wiFiManager.addParameter(&custom_text);
```

##### 5.3 Inject a custom bit of html in a configuration form element

Just add the bit you want added as the last parameter to the custom parameter constructor.

```cpp
ESP_AT_WMParameter custom_mqtt_server("server", "mqtt server", "iot.eclipse", 40, " readonly");
```

#### 6. Filter Networks

You can filter networks based on signal quality and show/hide duplicate networks.

- If you would like to filter low signal quality networks you can tell WiFiManager to not show networks below an arbitrary quality %;

```cpp
ESP_AT_wiFiManager.setMinimumSignalQuality(10);
```

will not show networks under 10% signal quality. If you omit the parameter it defaults to 8%;

- You can also remove or show duplicate networks (default is remove). Use this function to show (or hide) all networks.

```cpp
ESP_AT_wiFiManager.setRemoveDuplicateAPs(false);
```

---
---

### Example [ConfigOnSwitch](examples/ConfigOnSwitch)

#### 1. File [ConfigOnSwitch.ino](examples/ConfigOnSwitch/ConfigOnSwitch.ino)

```cpp
// Credits of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for this simple yet effective method
// For some STM32, there is only definition of Serial in variant.h, and is used for Serial/USB Debugging
// For example, in Nucleo-144 F767ZI original variant.h
//
// #define SERIAL_PORT_MONITOR     Serial
// #define SERIAL_PORT_HARDWARE    Serial
//
// To use ESP8266/ESP32-AT, we need another Serial, such as Serial1
// To do this, first, in corresponding variant.h, modify as follows:

// #define SERIAL_PORT_HARDWARE    Serial1
//
// then assign pins D0 = RX/D1 = TX to be Hardware Serial1 by putting in sketch as follows:
//
// #define EspSerial      SERIAL_PORT_HARDWARE    //Serial1
// HardwareSerial         Serial1(D0, D1);
//
// This must be included in defines.h for each board you'd like to use ESPSerial as Serial1
//
// The pin usage must be modified according to your boards.

#include "defines.h"

/* Trigger for inititating config mode is Pin D3 and also flash button on NodeMCU
   Flash button is convenient to use but if it is pressed it will stuff up the serial port device driver
   until the computer is rebooted on windows machines.
*/
const int TRIGGER_PIN = 22;   // Change the PIN to whatever you'd like
/*
   Alternative trigger pin. Needs to be connected to a button to use this pin. It must be a momentary connection
   not connected permanently to ground. Either trigger pin will work.
*/
const int TRIGGER_PIN2 = 23; // Change the PIN to whatever you'd like

// Indicates whether ESP has WiFi credentials saved from previous session
bool initialConfig = false;

void heartBeatPrint()
{
  static int num = 1;

  if (WiFi.status() == WL_CONNECTED)
    Serial.print("H");        // H means connected to WiFi
  else
    Serial.print("F");        // F means not connected to WiFi

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(" ");
  }
}

void check_status()
{
  static unsigned long checkstatus_timeout = 0;

#define HEARTBEAT_INTERVAL    10000L
  // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

void enterConfigPortal()
{
  //Local intialization. Once its business is done, there is no need to keep it around
  ESP_AT_WiFiManager ESP_AT_wiFiManager;

  ESP_AT_wiFiManager.setDebugOutput(true);

  ESP_AT_wiFiManager.setMinimumSignalQuality(-1);

  ESP_AT_wiFiManager.setAPChannel(1);

  // Default AP IP is 192.168.4.1. Uncomment to use different AP IP
  ESP_AT_wiFiManager.setAPStaticIPConfig(staticAP_IP);

  // Set static STA IP
  ESP_AT_wiFiManager.setSTAStaticIPConfig(IPAddress(192, 168, 2, 114));

  //Check if there is stored WiFi router/password credentials.
  //If not found, device will remain in configuration mode until switched off via webserver.
  Serial.println("Opening Config Portal.");

  Router_SSID = ESP_AT_wiFiManager.WiFi_SSID();
  Router_Pass = ESP_AT_wiFiManager.WiFi_Pass();

  if ( (Router_SSID != "") && ESP_AT_wiFiManager.isWiFiConfigValid() )
  {    
    if (ESP_AT_wiFiManager.connectWifi(Router_SSID, Router_Pass) == WL_CONNECTED)
    {
      Serial.println(F("Got stored Credentials. Try to connect first"));
      
      return;
    }
    
    ESP_AT_wiFiManager.setConfigPortalTimeout(60); //If no access point name has been previously entered disable timeout.
    Serial.println(F("Got stored Credentials but can't connect. Timeout 60s"));
  }
  else
    Serial.println(F("No stored or not valid Credentials. No timeout"));

  // SSID to uppercase
  ssid.toUpperCase();

  //Starts an AP and goes into a blocking loop awaiting configuration
  Serial.println("Start Config Portal, SSID = " + ssid + ", Pass = " + password);

  digitalWrite(LOCAL_PIN_LED, LED_ON); // Turn led on as we enter Config Portal

  if (!ESP_AT_wiFiManager.startConfigPortal((const char *) ssid.c_str(), password))
    Serial.println(F("Not connected to WiFi but continuing anyway."));
  else
    Serial.println(F("WiFi connected...yeey"));

  digitalWrite(LOCAL_PIN_LED, LED_OFF); // Turn led off as we exit Config Portal
}

void setup()
{
  // put your setup code here, to run once:
  // initialize the LED digital pin as an output.
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(TRIGGER_PIN2, INPUT_PULLUP);
  pinMode(LOCAL_PIN_LED, OUTPUT);
  digitalWrite(LOCAL_PIN_LED, LED_ON); // turn the LED on by making the voltage LOW to tell us we are in configuration mode.

  Serial.begin(115200);
  while (!Serial);

  unsigned long startedAt = millis();

#if USE_ESP32_AT
  Serial.println("\nStart ConfigOnSwitch with ESP32-AT WiFi module on " + String(BOARD_NAME));
#else
  Serial.println("\nStart ConfigOnSwitch with ESP8266-AT WiFi module on " + String(BOARD_NAME));
#endif

  Serial.println(ESP_AT_WIFIMANAGER_VERSION);
  
  // initialize serial for ESP module
  EspSerial.begin(115200);

  // initialize ESP module
  WiFi.init(&EspSerial);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

  enterConfigPortal();

  // For some unknown reason webserver can only be started once per boot up
  // so webserver can not be used again in the sketch.
#define WIFI_CONNECT_TIMEOUT        30000L
#define WHILE_LOOP_DELAY            200L
#define WHILE_LOOP_STEPS            (WIFI_CONNECT_TIMEOUT / ( 3 * WHILE_LOOP_DELAY ))

  startedAt = millis();

  while ( (WiFi.status() != WL_CONNECTED) && (millis() - startedAt < WIFI_CONNECT_TIMEOUT ) )
  {
    int i = 0;
    while ((!WiFi.status() || WiFi.status() >= WL_DISCONNECTED) && i++ < WHILE_LOOP_STEPS)
    {
      delay(WHILE_LOOP_DELAY);
    }
  }

  Serial.print(F("After waiting "));
  Serial.print((millis() - startedAt) / 1000);
  Serial.print(F(" secs in setup(), connect result is "));

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print(F("connected. Local IP: "));
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  // is configuration portal requested?
  if ((digitalRead(TRIGGER_PIN) == LOW) || (digitalRead(TRIGGER_PIN2) == LOW))
  {
    Serial.println("\nConfig Portal requested.");
    enterConfigPortal();
  }

  // put your main code here, to run repeatedly
  check_status();
}
```

#### 2. File [defines.h](examples/ConfigOnSwitch/defines.h)

```cpp
#ifndef defines_h
#define defines_h

#define DEBUG_ESP8266_AT_WEBSERVER_PORT Serial

// Debug Level from 0 to 4
#define _ESP_AT_LOGLEVEL_       1
#define DEBUG_WIFIMGR           true  //false

// Uncomment to use ESP32-AT commands
//#define USE_ESP32_AT      true

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(ESP8266_AT_USE_SAMD)
    #undef ESP8266_AT_USE_SAMD
  #endif
  #define ESP8266_AT_USE_SAMD      true
#endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(ESP8266_AT_USE_NRF528XX)
    #undef ESP8266_AT_USE_NRF528XX
  #endif
  #define ESP8266_AT_USE_NRF528XX      true
#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ESP8266_AT_USE_SAM_DUE)
    #undef ESP8266_AT_USE_SAM_DUE
  #endif
  #define ESP8266_AT_USE_SAM_DUE      true
#endif

#if  ( defined(STM32F0) || defined(STM32F1)  || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1)  || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) || defined(STM32L5))
  #if defined(ESP8266_AT_USE_STM32)
    #undef ESP8266_AT_USE_STM32
  #endif
  #define ESP8266_AT_USE_STM32      true
#endif

#ifdef CORE_TEENSY
  // For Teensy 4.1/4.0
  #define EspSerial Serial2   //Serial2, Pin RX2 : 7, TX2 : 8
  
  #if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #define BOARD_TYPE      "TEENSY 4.1/4.0"
  #elif defined(__MK66FX1M0__)
    #define BOARD_TYPE "Teensy 3.6"
  #elif defined(__MK64FX512__)
    #define BOARD_TYPE "Teensy 3.5"
  #elif defined(__MKL26Z64__)
    #define BOARD_TYPE "Teensy LC"
  #elif defined(__MK20DX256__)
    #define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
  #elif defined(__MK20DX128__)
    #define BOARD_TYPE "Teensy 3.0"
  #elif defined(__AVR_AT90USB1286__)
    #error Teensy 2.0++ not supported yet
  #elif defined(__AVR_ATmega32U4__)
    #error Teensy 2.0 not supported yet
  #else
    // For Other Boards
    #define BOARD_TYPE      "Unknown Teensy Board"
  #endif

#elif defined(ESP8266_AT_USE_SAMD)
  // For SAMD
  #define EspSerial Serial1
  
  #if defined(ARDUINO_SAMD_ZERO)
    #define BOARD_TYPE      "SAMD Zero"
  #elif defined(ARDUINO_SAMD_MKR1000)
    #define BOARD_TYPE      "SAMD MKR1000"
  #elif defined(ARDUINO_SAMD_MKRWIFI1010)
    #define BOARD_TYPE      "SAMD MKRWIFI1010"
  #elif defined(ARDUINO_SAMD_NANO_33_IOT)
    #define BOARD_TYPE      "SAMD NANO_33_IOT"
  #elif defined(ARDUINO_SAMD_MKRFox1200)
    #define BOARD_TYPE      "SAMD MKRFox1200"
  #elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
    #define BOARD_TYPE      "SAMD MKRWAN13X0"
  #elif defined(ARDUINO_SAMD_MKRGSM1400)
    #define BOARD_TYPE      "SAMD MKRGSM1400"
  #elif defined(ARDUINO_SAMD_MKRNB1500)
    #define BOARD_TYPE      "SAMD MKRNB1500"
  #elif defined(ARDUINO_SAMD_MKRVIDOR4000)
    #define BOARD_TYPE      "SAMD MKRVIDOR4000"
  #elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
    #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
  #elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M0_EXPRESS)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
  #elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
  #elif defined(ADAFRUIT_GEMMA_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
  #elif defined(ADAFRUIT_TRINKET_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
  #elif defined(ADAFRUIT_ITSYBITSY_M0)
    #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
  #elif defined(ARDUINO_SAMD_HALLOWING_M0)
    #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
  #elif defined(ADAFRUIT_METRO_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
  #elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
  #elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
  #elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYPORTAL)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
  #elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
  #elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
  #elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
  #elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
  #elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
  #elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
  #elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
    #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
  #elif defined(SEEED_WIO_TERMINAL)
    #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
  #elif defined(SEEED_FEMTO_M0)
    #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
  #elif defined(SEEED_XIAO_M0)
    #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
  #elif defined(Wio_Lite_MG126)
    #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
  #elif defined(WIO_GPS_BOARD)
    #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
  #elif defined(SEEEDUINO_ZERO)
    #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
  #elif defined(SEEEDUINO_LORAWAN)
    #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
  #elif defined(SEEED_GROVE_UI_WIRELESS)
    #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
  #elif defined(__SAMD21E18A__)
    #define BOARD_TYPE      "SAMD21E18A"
  #elif defined(__SAMD21G18A__)
    #define BOARD_TYPE      "SAMD21G18A"
  #elif defined(__SAMD51G19A__)
    #define BOARD_TYPE      "SAMD51G19A"
  #elif defined(__SAMD51J19A__)
    #define BOARD_TYPE      "SAMD51J19A"
  #elif defined(__SAMD51J20A__)
    #define BOARD_TYPE      "SAMD51J20A"
  #elif defined(__SAM3X8E__)
    #define BOARD_TYPE      "SAM3X8E"
  #elif defined(__CPU_ARC__)
    #define BOARD_TYPE      "CPU_ARC"
  #elif defined(__SAMD51__)
    #define BOARD_TYPE      "SAMD51"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#elif (ESP8266_AT_USE_NRF528XX)

  #if defined(NRF52840_FEATHER)
    #define BOARD_TYPE      "NRF52840_FEATHER_EXPRESS"
  #elif defined(NRF52832_FEATHER)
    #define BOARD_TYPE      "NRF52832_FEATHER"
  #elif defined(NRF52840_FEATHER_SENSE)
    #define BOARD_TYPE      "NRF52840_FEATHER_SENSE"
  #elif defined(NRF52840_ITSYBITSY)
    #define BOARD_TYPE      "NRF52840_ITSYBITSY_EXPRESS"
  #elif defined(NRF52840_CIRCUITPLAY)
    #define BOARD_TYPE      "NRF52840_CIRCUIT_PLAYGROUND"
  #elif defined(NRF52840_CLUE)
    #define BOARD_TYPE      "NRF52840_CLUE"
  #elif defined(NRF52840_METRO)
    #define BOARD_TYPE      "NRF52840_METRO_EXPRESS"
  #elif defined(NRF52840_PCA10056)
    #define BOARD_TYPE      "NORDIC_NRF52840DK"
  #elif defined(NINA_B302_ublox)
    #define BOARD_TYPE      "NINA_B302_ublox"
  #elif defined(NINA_B112_ublox)
    #define BOARD_TYPE      "NINA_B112_ublox"
  #elif defined(PARTICLE_XENON)
    #define BOARD_TYPE      "PARTICLE_XENON"
  #elif defined(MDBT50Q_RX)
    #define BOARD_TYPE      "RAYTAC_MDBT50Q_RX"
  #elif defined(ARDUINO_NRF52_ADAFRUIT)
    #define BOARD_TYPE      "ARDUINO_NRF52_ADAFRUIT"
  #else
    #define BOARD_TYPE      "nRF52 Unknown"
  #endif

#define EspSerial Serial1

#elif defined(ESP8266_AT_USE_SAM_DUE)
  // For SAM DUE
  #define EspSerial Serial1
  #define BOARD_TYPE      "SAM DUE"

#elif defined(ESP8266_AT_USE_STM32)
  // For STM32
  #warning EspSerial using SERIAL_PORT_HARDWARE, can be Serial or Serial1. See your board variant.h
  #define EspSerial     SERIAL_PORT_HARDWARE    //Serial1

  #if defined(STM32F0)
    #warning STM32F0 board selected
    #define BOARD_TYPE  "STM32F0"
  #elif defined(STM32F1)
    #warning STM32F1 board selected
    #define BOARD_TYPE  "STM32F1"
  #elif defined(STM32F2)
    #warning STM32F2 board selected
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #warning STM32F3 board selected
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #warning STM32F4 board selected
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)

    #if defined(ARDUINO_NUCLEO_F767ZI)
      #warning Nucleo-144 NUCLEO_F767ZI board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
      #define BOARD_TYPE  "NUCLEO_F767ZI"
      // RX TX
      HardwareSerial Serial1(D0, D1);
    #else
    
      #warning STM32F7 board selected
      #define BOARD_TYPE  "STM32F7"

    #endif
    
  #elif defined(STM32L0)
    #if defined(ARDUINO_NUCLEO_L053R8)
      #warning Nucleo-64 NUCLEO_L053R8 board selected, using HardwareSerial Serial1 @ pin D0/RX and D1/TX
      #define BOARD_TYPE  "NUCLEO_L053R8"
      // RX TX
      HardwareSerial Serial1(D0, D1);   // (PA3, PA2);
    #else
    
      #warning STM32L0 board selected
      #define BOARD_TYPE  "STM32L0"

    #endif
    
  #elif defined(STM32L1)
    #warning STM32L1 board selected
    #define BOARD_TYPE  "STM32L1"
  #elif defined(STM32L4)
    #warning STM32L4 board selected
    #define BOARD_TYPE  "STM32L4"
  #elif defined(STM32L5)
    #warning STM32L5 board selected
    #define BOARD_TYPE  "STM32L5"  
  #elif defined(STM32H7)
    #warning STM32H7 board selected
    #define BOARD_TYPE  "STM32H7"
  #elif defined(STM32G0)
    #warning STM32G0 board selected
    #define BOARD_TYPE  "STM32G0"
  #elif defined(STM32G4)
    #warning STM32G4 board selected
    #define BOARD_TYPE  "STM32G4"
  #elif defined(STM32WB)
    #warning STM32WB board selected
    #define BOARD_TYPE  "STM32WB"
  #elif defined(STM32MP1)
    #warning STM32MP1 board selected
    #define BOARD_TYPE  "STM32MP1"
  #else
    #warning STM32 unknown board selected
    #define BOARD_TYPE  "STM32 Unknown"
  #endif

#else
  // For Mega
  #define EspSerial Serial3
  #define BOARD_TYPE      "AVR Mega"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

// Must be before #include <ESP_AT_WiFiManager.h>
#define EEPROM_START        0

#include <ESP_AT_WiFiManager.h>              //https://github.com/khoih-prog/ESP_AT_WiFiManager

// Your Mega <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

// SSID and PW for Config Portal
#ifdef CORE_TEENSY
  String ssid = "ESP_AT_" + String(0x1ABCDEF, HEX);
#else
  String ssid = "ESP_AT_" + String(0xABCDEF, HEX);
#endif

const char* password = "ESP_AT_PW";

IPAddress staticAP_IP = IPAddress(192, 168, 100, 1);

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;

// Onboard LED I/O pin on board
const int LOCAL_PIN_LED = 13; // Pin 13, Controls the onboard LED.

#define LED_ON    HIGH
#define LED_OFF   LOW

#endif    //defines_h
```

---

### Debug Terminal Output Samples

### 1. ConfigOnSwitch on Adafruit Itsy-BItsy nRF52840 with ESP8266-AT shield

This is the terminal output when running [ConfigOnSwitch](examples/ConfigOnSwitch) example on **Adafruit Itsy-BItsy nRF52840 with ESP8266-AT shield**:

#### 1.1 Enter Config Portal

```
Start ConfigOnSwitch on NRF52840_ITSYBITSY
ESP_AT_WiFiManager v1.1.0
Opening Config Portal. *WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = SHD_ESP8266, SSID = HueNet1, PW = ****
*WM: Host Name = 
*WM: CCSum=0x8df,RCSum=0x0
*WM: InitCfgFile,sz=108
*WM: SaveCfgFile 
*WM: WCSum=0x7f4
*WM: OK
*WM: SaveBkUpCfgFile 
*WM: OK
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = blank, PW = blank
*WM: Host Name = blank
*WM: CCSum=0x7f4,RCSum=0x7f4
No stored Credentials. No timeout
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: Handle root
*WM: LoadCfgFile 
*WM: OK
*WM: Handle WiFi
*WM: Scan Network
*WM: DUP AP: 
*WM: DUP AP: 
*WM: HueNet1 / -28
*WM: bacau / -74
*WM: guest_24 / -77
*WM: Sent config page
*WM: WiFi save
*WM: SaveCfgFile 
*WM: WCSum=0x9c7
*WM: OK
*WM: SaveBkUpCfgFile 
*WM: OK
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = ****
*WM: Host Name = blank
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = ****
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HH
```

#### 1.2 Click `Save`

```
Start ConfigOnSwitch on NRF52840_ITSYBITSY
ESP_AT_WiFiManager v1.1.0
Opening Config Portal. *WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = ****
*WM: Host Name = blank
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = ****
*WM: Host Name = blank
Got stored Credentials. Timeout 60s
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: Static IP : 192.168.2.114
*WM: Timeout, connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
```

---

### 2. ConfigOnStartup on SAM-DUE with ESP32-AT shield

This is the terminal output when running [ConfigOnStartup](examples/ConfigOnStartup) example using **SAM-DUE with ESP32-AT shield**. The ESP32-AT firmware is AT version:2.1.0.0-dev / SDK version:v4.0.1-193-ge7ac221b4:

```
Start ConfigOnStartup on SAM DUE
ESP_AT_WiFiManager v1.1.0
[ESP_AT] AT+RST
[ESP_AT] ATE0
[ESP_AT] Use ESP32-AT Command
[ESP_AT] AT+CWMODE=1
[ESP_AT] AT+CIPMUX=1
[ESP_AT] AT+CIPDINFO=1
[ESP_AT] AT+CWAUTOCONN=0
[ESP_AT] AT+CWDHCP=1,1
[ESP_AT] AT+GMR
[ESP_AT] Firmware Init OK - v4.0.
[ESP_AT] AT+CIPSTATUS
Opening Config Portal. *WM: CCSum=0x7f4,RCSum=0x0
*WM: CCSum=0x7f4,RCSum=0x0
No stored Credentials. No timeout
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
[ESP_AT] AT+CWMODE=2
[ESP_AT] AT+CWDHCP=0,3
[ESP_AT] AT+CIPAP= 192.168.100.1
[ESP_AT] IP address set 192.168.100.1
[ESP_AT] AT+CWMODE= 3
AT+CWSAP= ESP_AT_ABCDEF ESP_AT_PW
AT+CWSAP= 1 3
[ESP_AT] AT+CWDHCP=1,3
[ESP_AT] Access point started ESP_AT_ABCDEF
*WM: AP IP: [ESP_AT] AT+CIPAP?
192.168.100.1
AT+CIPSERVER= 1 80
*WM: HTTP server on channel 1
*WM: Handle WiFi
*WM: Scan Network
[ESP_AT] AT+CWLAP
*WM: HueNet / -33
*WM: HueNet1 / -40
*WM: HueNetTek / -43
*WM: Sent config page
*WM: WiFi save
*WM: SaveDueFlash, CSum=2503
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = ****
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] AT+CWQAP
[ESP_AT] AT+CIPSTATUS
[ESP_AT] AT+RST
[ESP_AT] ATE0
[ESP_AT] Use ESP32-AT Command
[ESP_AT] AT+CWMODE=1
[ESP_AT] AT+CIPMUX=1
[ESP_AT] AT+CIPDINFO=1
[ESP_AT] AT+CWAUTOCONN=0
[ESP_AT] AT+CWDHCP=1,1
[ESP_AT] AT+CWDHCP=0,1
[ESP_AT] AT+CIPSTA= 192.168.2.114
[ESP_AT] IP address set 192.168.2.114
*WM: Static IP : 192.168.2.114
AT+CWJAP= HueNet1 ****
[ESP_AT] Connected to HueNet1
[ESP_AT] AT+CIPSTATUS
*WM: Connect result: WL_CONNECTED
[ESP_AT] AT+CIPSTATUS
WiFi connected...yeey
[ESP_AT] AT+CIPSTATUS
After waiting 0 secs in setup(), connect result is [ESP_AT] AT+CIPSTATUS
connected. Local IP: [ESP_AT] AT+CIFSR
192.168.2.114
[ESP_AT] AT+CIPSTATUS
H[ESP_AT] AT+CIPSTATUS
H
```

---

### 3. ConfigOnStartup on STM32 Nucleo-144 NUCLEO_F767ZI with ESP8266-AT shield

This is the terminal output when running [ConfigOnStartup](examples/ConfigOnStartup) example using **STM32 Nucleo-144 NUCLEO_F767ZI with ESP8266-AT shield**.

```
Start ConfigOnStartup on NUCLEO_F767ZI
ESP_AT_WiFiManager v1.1.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal. *WM: EEPROMsz:1024
*WM: CCSum=0x65a0,RCSum=0xffffffff
*WM: EEPROMsz:1024
*WM: CCSum=0x7f4,RCSum=0x0
No stored Credentials. No timeout
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: Handle root
*WM: EEPROMsz:1024
*WM: CCSum=0x7f4,RCSum=0x0
*WM: EEPROMsz:1024
*WM: CCSum=0x7f4,RCSum=0x0
*WM: Info
*WM: EEPROMsz:1024
*WM: CCSum=0x7f4,RCSum=0x0
*WM: EEPROMsz:1024
*WM: CCSum=0x7f4,RCSum=0x0
*WM: Sent info page
*WM: Handle root
*WM: EEPROMsz:1024
*WM: CCSum=0x7f4,RCSum=0x0
*WM: EEPROMsz:1024
*WM: CCSum=0x7f4,RCSum=0x0
*WM: Handle WiFi
*WM: Scan Network
*WM: HueNet / -22
*WM: HueNetTek / -36
*WM: HueNet1 / -46
*WM: Sent config page
*WM: WiFi save
*WM: SaveEEPROM,CSum=2503
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: EEPROMsz:1024
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHHHHHHHH
```
---

### 4. ConfigOnStartup on Seeeduino SEEED_XIAO_M0 with ESP8266-AT shield

This is the terminal output when running [ConfigOnStartup](examples/ConfigOnStartup) example using **Seeeduino SEEED_XIAO_M0 with ESP8266-AT shield**.

```
Start ConfigOnStartup on SEEED_XIAO_M0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal. *WM: CCSum=0x0,RCSum=0x0
*WM: CCSum=0x7f4,RCSum=0x0
No stored Credentials. No timeout
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: Handle root
*WM: CCSum=0x7f4,RCSum=0x0
*WM: CCSum=0x7f4,RCSum=0x0
*WM: Info
*WM: CCSum=0x7f4,RCSum=0x0
*WM: CCSum=0x7f4,RCSum=0x0
*WM: Sent info page
*WM: Handle root
*WM: CCSum=0x7f4,RCSum=0x0
*WM: CCSum=0x7f4,RCSum=0x0
*WM: Handle WiFi
*WM: Scan Network
*WM: DUP AP: 
*WM: HueNetTek / -25
*WM: HueNet1 / -32
*WM: HueNet2 / -42
*WM: Sent config page
*WM: WiFi save
*WM: SaveFlash,CSum=2504
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: CCSum=0x9c8,RCSum=0x9c8
*WM: Header = ESP_AT, SSID = HueNet2, PW = password
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHHHHHHHH
```

---

### 5. ConfigOnStartup on STM32 Nucleo-144 NUCLEO_F767ZI with ESP8266-AT shield with invalid data

This is the terminal output when running [ConfigOnStartup](examples/ConfigOnStartup) example using **STM32 Nucleo-144 NUCLEO_F767ZI with ESP8266-AT shield**.

### 5.1 Data OK => No Config Portal

```
Start ConfigOnStartup with ESP8266-AT WiFi module on NUCLEO_F767ZI
ESP_AT_WiFiManager v1.1.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal.
*WM: EEPROMsz:1024
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
Got stored Credentials. Try to connect first
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
H
```

### 5.2 Valid Data but no connection => Config Portal

```
Start ConfigOnStartup with ESP8266-AT WiFi module on NUCLEO_F767ZI
ESP_AT_WiFiManager v1.1.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal.
*WM: EEPROMsz:1024
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_DISCONNECTED
Got stored Credentials but can't connect. Timeout 60s
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: WiFi save
*WM: SaveEEPROM,CSum=2503
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHHHHH
```

---

### 6. ConfigOnSwitch on RASPBERRY_PI_PICO with ESP8266-AT shield

This is the terminal output when running [ConfigOnSwitch](examples/ConfigOnSwitch) example using **RASPBERRY_PI_PICO with ESP8266-AT shield**.

### 6.1 No Config Data => Config Portal

```
Start ConfigOnSwitch with ESP8266-AT WiFi module on RASPBERRY_PI_PICO
ESP_AT_WiFiManager v1.2.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal.
*WM: LoadCfgFile 
*WM: failed
*WM: LoadBkUpCfgFile 
*WM: failed
*WM: ======= Start Stored Config Data =======
*WM: Header = , SSID = , PW = 
*WM: Host Name = 
*WM: CCSum=0x1df0,RCSum=0xffffffff
*WM: InitCfgFile,sz=140
*WM: SaveCfgFile 
*WM: WCSum=0x7f4
*WM: OK
*WM: SaveBkUpCfgFile 
*WM: OK
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = blank, PW = blank
*WM: Host Name = blank
*WM: CCSum=0x7f4,RCSum=0x7f4
No stored or not valid Credentials. No timeout
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: Handle root
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = blank, PW = blank
*WM: Host Name = blank
*WM: CCSum=0x7f4,RCSum=0x7f4
*WM: Handle WiFi
*WM: Scan Network
*WM: DUP AP: 
*WM: HueNet1 / -32
*WM: HueNetTek / -37
*WM: dlink-4F96 / -79
*WM: Sent config page
*WM: WiFi save
*WM: SaveCfgFile 
*WM: WCSum=0x9c7
*WM: OK
*WM: SaveBkUpCfgFile 
*WM: OK
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHH
```

### 6.2 Forced Config => Config Portal

```
Start ConfigOnSwitch with ESP8266-AT WiFi module on RASPBERRY_PI_PICO
ESP_AT_WiFiManager v1.2.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal.
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
Got stored Credentials. Try to connect first
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
H
Config Portal requested.
Opening Config Portal.
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
Forced CP, No stored or not valid Credentials. No timeout
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: Handle root
*WM: Info
*WM: Sent info page
*WM: Handle root
*WM: Handle WiFi
*WM: Scan Network
*WM: DUP AP: Waterhome
*WM: HueNet1 / -30
*WM: HueNetTek / -34
*WM: HueNet2 / -55
*WM: Sent config page
*WM: WiFi save
*WM: SaveCfgFile 
*WM: WCSum=0x9c7
*WM: OK
*WM: SaveBkUpCfgFile 
*WM: OK
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
H
```

### 6.3 Data Saved => Connect WiFi

```
Start ConfigOnSwitch with ESP8266-AT WiFi module on RASPBERRY_PI_PICO
ESP_AT_WiFiManager v1.2.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal.
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = blank
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
Got stored Credentials. Try to connect first
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
H
```


---
---


### Debug

Debug is enabled by default on Serial. To disable, add before `startConfigPortal()`

```cpp
ESP_AT_wiFiManager.setDebugOutput(false);
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `ESP8266/ESP32-AT shield` AT-command or this library version.

Sometimes, the library will only work if you update the `ESP8266/ESP32-AT shield` core to the newer or older version because some function compatibility.

---
---

## Releases

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

---
---

### Issues ###

Submit issues to: [ESP_AT_WiFiManager issues](https://github.com/khoih-prog/ESP_AT_WiFiManager/issues)

---

### TO DO

1. Add support to more boards
2. Add more examples
3. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)

### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 4. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)**.
 5. Add support to SAM DUE.
 6. Add support to ESP32-AT
 7. Add support to W600 and WIS600-01S
 8. Add support to all **STM32F/L/H/G/WB/MP1**
 9. Add support to **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
10. Use more efficient [FlashStorage_SAMD](https://github.com/khoih-prog/FlashStorage_SAMD) and [FlashStorage_STM32](https://github.com/khoih-prog/FlashStorage_STM32)
11. Add Table-of-Contents and Version String
12. Enforce WiFi PWD minimum length of 8 chars
13. Permit auto-connect without waiting for Config Portal if stored data is valid and WiFi test connection is OK.
14. Add support to new STM32 core v2.0.0 and new STM32L5 boards.
15. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico) 

---
---

### Contributions and Thanks

1. Based on and modified from [Tzapu](https://github.com/tzapu/WiFiManager) and [KenTaylor's version]( https://github.com/kentaylor/WiFiManager)
2. Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing. Without that, support to nRF52, especially **NINA_B302_ublox/NINA_B112_ublox running as nRF52840/nRF52832**, has never been started and finished.

<table>
  <tr>
    <td align="center"><a href="https://github.com/tzapu"><img src="https://github.com/tzapu.png" width="100px;" alt="tzapu"/><br /><sub><b>⭐️ tzapu</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/kentaylor"><img src="https://github.com/kentaylor.png" width="100px;" alt="kentaylor"/><br /><sub><b>⭐️ Ken Taylor</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
  </tr> 
</table>


### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang


