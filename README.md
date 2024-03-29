# ESP_AT_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WiFiManager.svg?)](https://www.ardu-badge.com/ESP_AT_WiFiManager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP_AT_WiFiManager.svg)](https://github.com/khoih-prog/ESP_AT_WiFiManager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP_AT_WiFiManager.svg)](http://github.com/khoih-prog/ESP_AT_WiFiManager/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Why do we need this ESP_AT_WiFiManager library](#why-do-we-need-this-esp_at_wifimanager-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently Supported AT-command shields](#currently-supported-at-command-shields)
* [Changelog](changelog.md)
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
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
  * [13. For Seeeduino nRF52840 boards](#13-For-Seeeduino-nRF52840-boards)
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
  * [7. ConfigOnStartup on MBED RASPBERRY_PI_PICO with ESP8266-AT shield](#7-configonstartup-on-mbed-raspberry_pi_pico-with-esp8266-at-shield)
  * [8. AutoConnect on MBED RASPBERRY_PI_PICO with ESP8266-AT shield](#8-autoconnect-on-mbed-raspberry_pi_pico-with-esp8266-at-shield)
  * [9. ConfigOnStartup with ESP32-AT WiFi module on WIZNET_WIZFI360_EVB_PICO](#9-ConfigOnStartup-with-ESP32-AT-WiFi-module-on-WIZNET_WIZFI360_EVB_PICO)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
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

The **RP2040-based boards, such as Nano_RP1040_Connect, RASPBERRY_PI_PICO**, are currently supported using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico) or [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) with Blynk/WiFiManager features thanks to **LittleFS** support.

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
 
 7. RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).

 8. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
 
 9. **WIZNET_WIZFI360_EVB_PICO** using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico)

#### WIZNET_WIZFI360_EVB_PICO

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/raw/master/Images/WIZNET_WIZFI360_EVB_PICO.png">
</p>


---

#### Currently Supported AT-command shields

 1. `ESP8266-AT-command` shield
 2. `ESP32-AT-command` shield
 3. `W600` and `WIS600-01S` AT-command shield
 4. `WizFi360` AT-command shield
 
#### WIZFI360
 
<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/raw/master/Images/wizfi360-pa.png">
</p>

 
---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino AVR core 1.8.6+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Arduino Core for STM32 v2.4.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.). [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
 4. [`Teensy core v1.57+`](https://github.com/PaulStoffregen/cores) for Teensy 4.1.  [![GitHub release](https://img.shields.io/github/release/PaulStoffregen/cores.svg)](https://github.com/PaulStoffregen/cores/releases/latest)
 5. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 6. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 7. [`Adafruit SAMD core 1.7.11+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 8. [`Seeeduino SAMD core 1.8.3+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 9. [`Adafruit nRF52 v1.3.0`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
10. [`Arduino mbed_rp2040 core 3.5.4+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino RP2040-based boards, such as **Arduino Nano RP2040 Connect, RASPBERRY_PI_PICO, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
11. [`Earle Philhower's arduino-pico core v2.7.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
12. [`ESP8266_AT_WebServer library v1.7.1+`](https://github.com/khoih-prog/ESP8266_AT_WebServer) to be able to support ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)
13. [`FlashStorage_SAMD library v1.3.2+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases/latest). Or [`Platform.io FlashStorage_SAMD library v1.0.0+`](https://platformio.org/lib/show/11242/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.)
14. [`FlashStorage_STM32 library v1.2.0+`](https://github.com/khoih-prog/FlashStorage_STM32) for STM32F/L/H/G/WB/MP1 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/FlashStorage_STM32.svg?)](https://www.ardu-badge.com/FlashStorage_STM32)
15. [`DueFlashStorage library v1.0.0+`](https://github.com/sebnil/DueFlashStorage) for SAM DUE. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DueFlashStorage.svg?)](https://www.ardu-badge.com/DueFlashStorage)
16. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52 boards.
17. [`Ai-Thinker AT Firmware v1.5.4`](AT_Firmwares/At_firmware_bin1.54.zip) or [`AT Firmware v1.7.4.0`](AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip) for ESP8266-AT shields.
18. [`AT version_2.1.0.0_dev`](AT_Firmwares/AT_version_2.1.0.0_dev.zip) for ESP32-AT shields.
19. `AT version_1.1.4` for WIS600-01S and W600-AT WiFi shields.

---

### Important Notes about AT Firmwares

### 1. Firmwares tested OK with ESP8266 AT shields

  - [`Ai-Thinker AT Firmware v1.5.4`](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/AT_Firmwares/At_firmware_bin1.54.zip)
  
    ```cpp
    AT version:1.1.0.0(May 11 2016 18:09:56)
    SDK version:1.5.4(baaeaebb)
    Ai-Thinker Technology Co. Ltd.
    Jun 13 2016 11:29:20
    ```
  - [`AT Firmware v1.7.4.0`](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip)
  
    ```cpp
    AT version:1.7.4.0(May 11 2020 19:13:04)
    SDK version:3.0.4(9532ceb)
    compile time:May 27 2020 10:12:17
    Bin version(Wroom 02):1.7.4
    ```
    
  - [`WIS600-01S`](https://www.aliexpress.com/item/32956707239.html) and [`W600`](https://www.seeedstudio.com/w600.html) using either ESP8266 or ESP32-AT commands and stock firmware
  
    ```cpp
    AT version:1.1.4(Dec 05 2018 11:06:45)
    SDK version:3.0.0
    Dec 05 2018 11:06:45
    ```
  
  
### 2. Firmwares tested OK with ESP32 AT shields

  - [`AT version_2.1.0.0_dev`](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/AT_Firmwares/AT_version_2.1.0.0_dev.zip)
    
    ```cpp
    AT version:2.1.0.0-dev(4f6b92c - Jun 10 2020 10:36:54)
    SDK version:v4.0.1-193-ge7ac221b4
    compile time(b85a8df):Jun 18 2020 14:00:59
    Bin version:2.0.0(WROOM-32)
    ```
    
    See instructions at [AT Command Core](https://github.com/espressif/esp-at) and [ESP_AT_Get_Started](https://github.com/espressif/esp-at/blob/master/docs/en/get-started/ESP_AT_Get_Started.md)
  
3. Upload [`AT Firmware v1.7.4.0`](https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/master/AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip) bin files to correct locations as follows:

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
5. Compatible AT-Firmare version will be updated. Check for all supported AT Firmwares and download them from [AT_Firmwares](https://github.com/khoih-prog/ESP_AT_WiFiManager/tree/master/AT_Firmwares).
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
3. Install [**ESP_AT_WiFiManager** library](https://registry.platformio.org/libraries/khoih-prog/ESP_AT_WiFiManager) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/ESP_AT_WiFiManager/installation). Search for **ESP_AT_WiFiManager** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

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
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

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
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.11) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.11). 

Supposing the Adafruit SAMD core version is 1.7.11. These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.11/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.3) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3). 

Supposing the Seeeduino SAMD core version is 1.8.3. These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
these files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.4.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.4.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.4. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.4/cores/ambd/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/ambd/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.9.0. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.9.0/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino RP2040 core version is 2.7.2. These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---

#### 13. For Seeeduino nRF52840 boards

**To be able to compile and run on Xiao nRF52840 boards**, you have to copy the whole [nRF52 1.0.0](Packages_Patches/Seeeduino/hardware/nrf52/1.0.0) directory into Seeeduino nRF52 directory (~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0). 

Supposing the Seeeduino nRF52 version is 1.0.0. These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/platform.txt`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/1.0.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/platform.txt`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`**
- **`~/.arduino15/packages/Seeeduino/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**


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
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/raw/master/Images/Main.png">
</p>

Select `Information` to enter the Info page where the board info will be shown

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/raw/master/Images/Info.png">
</p>

Select `Configuration` to enter this page where you can select an AP and specify its WiFi Credentials

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WiFiManager/raw/master/Images/Configuration.png">
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

https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/4d5413918826a1e747b1d2bb6807153ef334652d/examples/ConfigOnSwitch/ConfigOnSwitch.ino#L25-L241

#### 2. File [defines.h](examples/ConfigOnSwitch/defines.h)

https://github.com/khoih-prog/ESP_AT_WiFiManager/blob/4d5413918826a1e747b1d2bb6807153ef334652d/examples/ConfigOnSwitch/defines.h#L15-L395

---

### Debug Terminal Output Samples

### 1. ConfigOnSwitch on Adafruit Itsy-BItsy nRF52840 with ESP8266-AT shield

This is the terminal output when running [ConfigOnSwitch](examples/ConfigOnSwitch) example on **Adafruit Itsy-BItsy nRF52840 with ESP8266-AT shield**:

#### 1.1 Enter Config Portal

```
Start ConfigOnSwitch on NRF52840_ITSYBITSY
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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
ESP_AT_WiFiManager v1.4.0
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

### 7. ConfigOnStartup on MBED RASPBERRY_PI_PICO with ESP8266-AT shield

This is the terminal output when running [ConfigOnStartup](examples/ConfigOnStartup) example using **MBED RASPBERRY_PI_PICO with ESP8266-AT shield**.


```
Start ConfigOnStartup with ESP8266-AT WiFi module on MBED RASPBERRY_PI_PICO
ESP_AT_WiFiManager v1.4.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal.
*WM: LittleFS size (KB) = 64
*WM: LittleFS Mount OK
*WM: LoadCfgFile 
*WM: failed
*WM: LoadBkUpCfgFile 
*WM: failed
*WM: CCSum=0x1d51,RCSum=0xd
*WM: InitCfgFile,sz=140
*WM: SaveCfgFile 
*WM: WCSum=0x899
*WM: OK
*WM: SaveBkUpCfgFile 
*WM: OK
*WM: LittleFS size (KB) = 64
*WM: LittleFS Mount OK
*WM: LoadCfgFile 
*WM: OK
*WM: CCSum=0x899,RCSum=0x899
No stored or not valid Credentials. No timeout
Start Config Portal, SSID = ESP_AT_ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_ABCDEF
*WM: AP PW: ESP_AT_PW
*WM: Custom AP IP: 192.168.100.1
*WM: AP IP: 192.168.100.1
*WM: HTTP server on channel 1
*WM: Handle root
*WM: LittleFS size (KB) = 64
*WM: LittleFS Mount OK
*WM: LoadCfgFile 
*WM: OK
*WM: CCSum=0x899,RCSum=0x899
*WM: LittleFS size (KB) = 64
*WM: LittleFS Mount OK
*WM: LoadCfgFile 
*WM: OK
*WM: CCSum=0x899,RCSum=0x899
*WM: Handle WiFi
*WM: Scan Network
*WM: DUP AP: 
*WM: DUP AP: 
*WM: HueNetTek / -28
*WM: HueNet1 / -32
*WM:  / -81
*WM: Sent config page
*WM: WiFi save
*WM: SaveCfgFile 
*WM: WCSum=0xa6c
*WM: OK
*WM: SaveBkUpCfgFile 
*WM: OK
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: LittleFS size (KB) = 64
*WM: LittleFS Mount OK
*WM: LoadCfgFile 
*WM: OK
*WM: CCSum=0xa6c,RCSum=0xa6c
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = MBED-RP2040
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 2 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHH
```

---

### 8. AutoConnect on MBED RASPBERRY_PI_PICO with ESP8266-AT shield

This is the terminal output when running [AutoConnect](examples/AutoConnect) example using **MBED RASPBERRY_PI_PICO with ESP8266-AT shield**.


```
Start AutoConnect with ESP8266-AT WiFi module on MBED RASPBERRY_PI_PICO
ESP_AT_WiFiManager v1.4.0
[ESP_AT] Use ES8266-AT Command
Opening Config Portal.
*WM: LittleFS size (KB) = 64
*WM: LittleFS Mount OK
*WM: LoadCfgFile 
*WM: OK
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = MBED-RP2040
*WM: CCSum=0x9c7,RCSum=0x9c7
*WM: Header = ESP_AT, SSID = HueNet1, PW = password
*WM: Host Name = MBED-RP2040
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Use ES8266-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
Got stored Credentials. Try to connect first
Exit Config Portal
HHHHHHHHH
```

---

### 9. ConfigOnStartup with ESP32-AT WiFi module on WIZNET_WIZFI360_EVB_PICO

This is the terminal output when running [ConfigOnStartup](examples/ConfigOnStartup) example using **WIZNET_WIZFI360_EVB_PICO with WIZFI360 shield**.


```
Start ConfigOnStartup with ESP32-AT WiFi module on WIZNET_WIZFI360_EVB_PICO
ESP_AT_WiFiManager v1.4.0
[ESP_AT] Using ESP32-AT Command
Opening Config Portal.
*WM: LoadCfgFile 
*WM: OK
*WM: CCSum=0x8f6,RCSum=0x8f6
*WM: ======= Start Stored Config Data =======
*WM: Header = ESP_AT, SSID = HueNet, PW = 12345678
*WM: Host Name = RP2040
*WM: Connect wifi with new params
*WM: Data cleared
[ESP_AT] Using ESP32-AT Command
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
Got stored Credentials. Try to connect first
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHHHHHHHH
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

### Issues ###

Submit issues to: [ESP_AT_WiFiManager issues](https://github.com/khoih-prog/ESP_AT_WiFiManager/issues)

---

### TO DO

1. Add support to more boards
2. Add more examples

---

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
15. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
16. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
17. Add support to **Arduino Nano RP2040 Connect** using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).
18. Add support to WizNet `WizFi360`, such as `WIZNET_WIZFI360_EVB_PICO` using `arduino-pico` core


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

Copyright (C) 2020- Khoi Hoang


