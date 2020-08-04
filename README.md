## ESP_AT_WM_Lite (Light Weight Credentials / WiFi Manager for ESP8266 AT shields)

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WM_Lite.svg?)](https://www.ardu-badge.com/ESP_AT_WM_Lite)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/ESP_AT_WM_Lite.svg)](https://github.com/khoih-prog/ESP_AT_WM_Lite/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/ESP_AT_WM_Lite/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/ESP_AT_WM_Lite.svg)](http://github.com/khoih-prog/ESP_AT_WM_Lite/issues)

---

New recent features:

- ***MultiWiFi*** feature for configuring/auto(re)connecting ***ESP8266/ESP32-AT*** shields to the available MultiWiFi APs at runtime.
- ***DoubleDetectDetector*** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable ***Config Portal Title*** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.

### New Version v1.0.4

1. Add support to ***ESP32-AT WiFi shields.***
2. Add support to ***WIS600-01S/W600-AT WiFi shields.***
3. Modify LOAD_DEFAULT_CONFIG_DATA logic.
4. Enhance MultiWiFi connection logic. 
5. Fix WiFi Status bug.

### New Version v1.0.3

1. Add support to ***nRF52 (AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)**. Dynamic custom parameters to be saved ***automatically in LittleFS***.
2. Add MultiWiFi features for WiFi
3. Add DoubleResetDetector (DRD) feature.
4. Restructure examples separate Credentials / Defines / Dynamic Params / Code.
5. Drop support to Teensy boards.

### New Version v1.0.2

1. Add support to ***SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.) and SAM DUE***.
2. WiFi Password max length is 63, according to WPA2 standard.
3. Permit to input special chars such as ***~,!,@,#,$,%,^,*,&*** into data fields.
4. Fix bug

#### New in v1.0.1

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, SAMD EEPROM-emulated FlashStorage or SAM DUE DueFlashStorage***.

---

## Features

This library is a Light Weight Credentials / WiFi Manager for ESP8266 AT shields, specially designed to support ***AVR Mega, SAM DUE, SAMD21, SAMD51, nRF52, STM32, etc. boards running ESP8266/ESP32-AT-command shields.*** with smaller memory (64+K bytes)

The AVR-family boards (UNO, Nano, etc.) are ***not supported*** as they don't have enough memory to run Config Portal WebServer.

This is a Credentials / WiFi Connection Manager, permitting the addition of custom parameters to be configured in Config Portal. The parameters then will be saved automatically, ***without the complicated callback functions*** to handle data saving / retrieving.

If you have used the full-fledge WiFiManager such as :
1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)
3. [`ESP_WiFiManager`](https://github.com/khoih-prog/ESP_WiFiManager)

and have to write complicated callback functions to save custom parameters in SPIFFS, you'd appreciate the simplicity of this Light-Weight Credentials / WiFiManager

The web configuration portal, served from the `ESP8266 AT-command shields` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

---

## Prerequisite
 1. [`Arduino IDE 1.8.12+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino Core for STM32 v1.9.0+`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
 3. [`Adafruit nRF52 core v0.20.5+`](www.adafruit.com) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, ***NINA_B302_ublox, NINA_B112_ublox***, etc.
 4. [`Arduino SAM DUE core 1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 5. [`Arduino SAMD core 1.8.7+`](https://www.arduino.cc/en/Guide/ArduinoM0) for SAMD ARM Cortex-M0+ boards
 6. [`Adafruit SAMD core 1.6.0+`](https://www.adafruit.com/) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.)
 7. [`ESP8266_AT_WebServer library v1.0.12+`](https://github.com/khoih-prog/ESP8266_AT_WebServer). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer)
 8. [`FlashStorage_SAMD library v1.0.0+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.) and SAMD51 boards (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)
 9. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE
10. [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52
11. [`DoubleResetDetector_Generic v1.0.2+`](https://github.com/khoih-prog/DoubleResetDetector_Generic). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic)
12. [`Ai-Thinker AT Firmware v1.5.4`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/At_firmware_bin1.54.zip) or [`AT Firmware v1.7.4.0`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_Firmware_bin_1.7.4.0.zip) for ESP8266-AT WiFi shields.
13. [`AT version_2.1.0.0_dev`](https://github.com/khoih-prog/ESP8266_AT_WebServer/blob/master/AT_Firmwares/AT_version_2.1.0.0_dev.zip) for ESP32-AT WiFi shields.
14. `AT version_1.1.4` for WIS600-01S and W600-AT WiFi shields.

---

### Important Notes about AT Firmwares

1. Tested OK with for ESP8266-AT shields:
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
  
  
2. Tested OK with for ESP32-AT shields:
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
The best and easiest way is to use `Arduino Library Manager`. Search for `ESP_AT_WM_Lite`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WM_Lite.svg?)](https://www.ardu-badge.com/ESP_AT_WM_Lite) for more detailed instructions.

### Manual Install

1. Navigate to [ESP_AT_WM_Lite](https://github.com/khoih-prog/ESP_AT_WM_Lite) page.
2. Download the latest release `ESP_AT_WM_Lite-master.zip`.
3. Extract the zip file to `ESP_AT_WM_Lite-master` directory 
4. Copy whole 
  - `ESP_AT_WM_Lite-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:
1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install **ESP_AT_WM_Lite** library by using [Library Manager](https://docs.platformio.org/en/latest/librarymanager/). Search for ***ESP_AT_WM_Lite*** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](examples/platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically.

---

### Packages' Patches

 1. ***To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards***, you have to copy the whole [nRF52 0.20.5](Packages_Patches/adafruit/hardware/nrf52/0.20.5) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5). 

Supposing the Adafruit nRF52 version is 0.20.5. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/variants/NINA_B112_ublox/variant.cpp`
- ***`~/.arduino15/packages/adafruit/hardware/nrf52/0.20.5/cores/nRF5/Udp.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- ***`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`***

 2. ***To be able to compile and run on Teensy boards***, you have to copy the file [Teensy boards.txt](Packages_Patches/hardware/teensy/avr/boards.txt) into Teensy hardware directory (./arduino-1.8.12/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.12. This file must be copied into the directory:

- `./arduino-1.8.12/hardware/teensy/avr/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`

 3. ***To be able to compile and run on SAM DUE boards***, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

 4. ***To be able to compile without error and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD cores 1.8.7](Packages_Patches/arduino/hardware/samd/1.8.7) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.7).
 
Supposing the Arduino SAMD version is 1.8.7. These files must be copied into the directory:
- `~/.arduino15/packages/arduino/hardware/samd/1.8.7/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.7/cores/arduino/Arduino.h`***

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

 5. ***To be able to automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the file [Adafruit SAMD platform.txt](Packages_Patches/adafruit/hardware/samd/1.6.0) into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.6.0). 

Supposing the Adafruit SAMD core version is 1.6.0. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.6.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`

 6. ***To be able to automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the file [Seeeduino SAMD platform.txt](Packages_Patches/Seeeduino/hardware/samd/1.7.7) into Adafruit samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.7.7). 

Supposing the Seeeduino SAMD core version is 1.7.7. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.7.7/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`

7. ***To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards***, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/1.9.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/1.9.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 1.9.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/1.9.0/variants/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/NUCLEO_L053R8/variant.h`

---

## How It Works

- The [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield) is that a new `ESP8266 AT shield` will start a WiFi configuration portal when powered up, but has no valid stored Credentials. 
- There are ***maximum 3 more custom parameters*** added in the sketch which you can use in your program later. In the example, they are: Blynk Server, Token and Blynk Port.
- Using any WiFi enabled device with a browser (computer, phone, tablet) connect to the newly created AP and type in the configurable AP IP address (default 192.168.4.1). The Config Portal AP channel (default 10) is also configurable to ***avoid conflict*** with other APs.
- The Config Portal is auto-adjusted to fix the 2 static parameters (WiFi SSID/PWD) as well as 6 more dynamic custom parameters.
- After the custom data entered, and `Save` button pressed, the configuration data will be saved in host's non-volatile memory, then the board reboots.
- If there is valid stored Credentials, it'll go directly to connect to WiFi without starting / using the Config Portal.
- `ESP8266 AT shield` will try to connect. If successful, the dynamic DHCP or configured static IP address will be displayed in the configuration portal. 
- The `ESP8266 AT shield` WiFi Config Portal network and Web Server will shutdown to return control to the sketch code.

---

### How to use

- Include in your sketch
```cpp

// Select depending on board
#define EspSerial Serial1

#include <Esp8266_AT_WM_Lite_nRF52.h>

#define HOST_NAME   "nRF52-ESP_AT"

// SSID and PW for Config Portal
String portal_ssid      = "nRF52-CfgPrtl-SSID";
String portal_password  = "nRF52-CfgPrtl-PW";

ESP_AT_WiFiManager_Lite* ESP_AT_WiFiManager; 

// Your nRF52 <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200
```

### How to add dynamic parameters from sketch

- To add custom parameters, just modify from the example below

```
#define USE_DYNAMIC_PARAMETERS      true

/////////////// Start dynamic Credentials ///////////////

//Defined in <Esp8266_AT_WM_Lite_nRF52.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt-server";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";


MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
};

// Due to notorious 2K buffer limitation of ESO8266-AT shield, the NUM_MENU_ITEMS is limited to max 3
// to avoid WebServer not working due to HTML data larger than 2K can't be sent successfully
// The items with index larger than 3 will be ignored

uint16_t NUM_MENU_ITEMS = min( 3, sizeof(myMenuItems) / sizeof(MenuItem));  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif

/////// // End dynamic Credentials ///////////

```

- If you don't need to add dynamic parameters, use in sketch

```
#define USE_DYNAMIC_PARAMETERS      false

```

### How to open Config Portal

- When you want to open a config portal, just add

```cpp
ESP_AT_WiFiManager = new ESP_AT_WiFiManager_Lite(&EspSerial, ESP8266_BAUD);

// Optional to change default AP IP(192.168.4.1)
//ESP_AT_WiFiManager->setConfigPortalIP(IPAddress(192, 168, 220, 1));

// Use channel(0) for random AP WiFi channel
ESP_AT_WiFiManager->setConfigPortalChannel(1);

// Personalized portal_ssid and password, e.g. CfgPrtl-SSID and CfgPrtl-PW
ESP_AT_WiFiManager->setConfigPortal(portal_ssid, portal_password);

ESP_AT_WiFiManager->begin();
```

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs, call 

```cpp
ESP_AT_WiFiManager->setConfigPortalChannel(newChannel);
```

- To use different static AP IP (not use default `192.168.4.1`), call 
```cpp
ESP_AT_WiFiManager->setConfigPortalIP(IPAddress(xxx,xxx,xxx,xxx));
```

While in AP mode, connect to it using its `SSID` (Personalized SSID or "ESP_AT_XXXXXX") / `Password` (Personalized PW or "MyESP_AT_XXXXXX"), then connect a Web-Browser to the Portal AP IP, default `192.168.4.1`, configure wifi and dynamic Credentials, then click `Save`. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect to one of the configured WiFi APs.


Once Credentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.

---

### Examples:

1. [Mega_ESP8266Shield](examples/Mega_ESP8266Shield)
2. [SAMD_ESP8266Shield](examples/SAMD_ESP8266Shield)
3. [SAM_DUE_ESP8266Shield](examples/SAM_DUE_ESP8266Shield)
4. [STM32_ESP8266Shield](examples/STM32_ESP8266Shield)
5. [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)

---

## So, how it works?
In `Configuration Portal Mode`, it starts an AP named `ESP_AT_XXXXXX`. Connect to it using the `configurable password` you can define in the code. For example, `MyESP_AT_XXXXXX` (see examples):

```cpp
// SSID and PW for Config Portal
String ssid = "ESP_AT_" + String(0x1ABCDEF, HEX);
const char* password = "ESP_AT_PW";
```
After you connected, please, go to http://192.168.4.1 or newly configured AP IP, you'll see this `Main` page:

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WM_Lite/blob/master/pics/Main.png">
</p>

Enter your credentials, 

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WM_Lite/blob/master/pics/Input.png">
</p>

then click `Save`. 

<p align="center">
    <img src="https://github.com/khoih-prog/ESP_AT_WM_Lite/blob/master/pics/Save.png">
</p>

The WiFi Credentials will be saved and the board connect to the selected WiFi AP.

If you're already connected to a listed WiFi AP and don't want to change anything, just select `Exit` from the `Main` page to reboot the board and connect to the previously-stored AP. The WiFi Credentials are still intact.

---

### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

1. To load [Default Credentials](examples/nRF52_ESP8266Shield/Credentials.h)
```
// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

2. To use system default to load "blank" when there is no valid Credentials
```
// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

3. Example of [Default Credentials](examples/nRF52_ESP8266Shield/Credentials.h)

```cpp
/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header, just add board_name 
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [24];
  int  checkSum;
} ESP8266_AT_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

// This feature is primarily used in development to force a known set of values as Config Data
// It will NOT force the Config Portal to activate. Use DRD or erase Config Data with Blynk.clearConfigData()

// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
//bool LOAD_DEFAULT_CONFIG_DATA = true;

// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;


ESP8266_AT_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "SHD_ESP8266",
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  //char board_name     [24];
  "nRF52-ESP_AT",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

ESP8266_AT_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////
```
---

### Example [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield)


#### 1. File [nRF52_ESP8266Shield.ino](examples/nRF52_ESP8266Shield/nRF52_ESP8266Shield.ino)

```
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

ESP_AT_WiFiManager_Lite* ESP_AT_WiFiManager;

void heartBeatPrint(void)
{
  static int num = 1;

  if (ESP_AT_WiFiManager->getWiFiStatus())
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

  //KH
#define HEARTBEAT_INTERVAL    20000L
  // Print hearbeat every HEARTBEAT_INTERVAL (20) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart nRF52_ESP8266Shield on " + String(BOARD_TYPE));

  // initialize serial for ESP module
  EspSerial.begin(115200);

  ESP_AT_WiFiManager = new ESP_AT_WiFiManager_Lite(&EspSerial, ESP8266_BAUD);
 
  // Optional to change default AP IP(192.168.4.1)
  //ESP_AT_WiFiManager->setConfigPortalIP(IPAddress(192, 168, 220, 1));
  // Use channel(0) for random AP WiFi channel
  ESP_AT_WiFiManager->setConfigPortalChannel(1);

  // Personalized portal_ssid and password
  ESP_AT_WiFiManager->setConfigPortal(portal_ssid, portal_password);

  ESP_AT_WiFiManager->begin();
}

#if USE_DYNAMIC_PARAMETERS
void displayCredentials(void)
{
  Serial.println("\nStored Dynamic Params:");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}
#endif

void loop()
{
  ESP_AT_WiFiManager->run();
  check_status();

#if USE_DYNAMIC_PARAMETERS
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
#endif
}
```

#### 2. File [defines.h](examples/nRF52_ESP8266Shield/defines.h)

```cpp
#ifndef defines_h
#define defines_h

/* Comment this out to disable prints and save space */
#define DRD_GENERIC_DEBUG             true

#define USE_NEW_WEBSERVER_VERSION     true  //false
#define _ESP_AT_LOGLEVEL_             1

/* Comment this out to disable prints and save space */
#define ESP_AT_DEBUG_OUTPUT           Serial

#define ESP_AT_DEBUG                  true

// Uncomment to use ESP32-AT commands
//#define USE_ESP32_AT                  true

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
#if defined(ESP8266_AT_USE_NRF528XX)
#undef ESP8266_AT_USE_NRF528XX
#endif
#define ESP8266_AT_USE_NRF528XX      true
#else
#error This code is intended to run only on the nRF52 boards ! Please check your Tools->Board setting.
#endif

#if (ESP8266_AT_USE_NRF528XX)

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

#endif    //ESP8266_AT_USE_NRF528XX

#include <Esp8266_AT_WM_Lite_nRF52.h>

#define HOST_NAME   "nRF52-ESP_AT"

// SSID and PW for Config Portal
String portal_ssid      = "CfgPrtl-SSID";
String portal_password  = "CfgPrtl-PW";

// Your nRF52 <-> ESP8266 baud rate:
#define ESP8266_BAUD 115200

#endif      //defines_h
```

#### 3. File [Credentials.h](examples/nRF52_ESP8266Shield/Credentials.h)

```cpp
#ifndef Credentials_h
#define Credentials_h

#include "defines.h"

/// Start Default Config Data //////////////////

/*
#define SSID_MAX_LEN      32
//From v1.0.3, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN      64

typedef struct
{
  char wifi_ssid[SSID_MAX_LEN];
  char wifi_pw  [PASS_MAX_LEN];
}  WiFi_Credentials;

#define NUM_WIFI_CREDENTIALS      2

// Configurable items besides fixed Header, just add board_name 
#define NUM_CONFIGURABLE_ITEMS    ( ( 2 * NUM_WIFI_CREDENTIALS ) + 1 )
////////////////

typedef struct Configuration
{
  char header         [16];
  WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  char board_name     [24];
  int  checkSum;
} ESP8266_AT_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

// This feature is primarily used in development to force a known set of values as Config Data
// It will NOT force the Config Portal to activate. Use DRD or erase Config Data with Blynk.clearConfigData()

// Used mostly for development and debugging. FORCES default values to be loaded each run.
// Config Portal data input will be ignored and overridden by DEFAULT_CONFIG_DATA
//bool LOAD_DEFAULT_CONFIG_DATA = true;

// Used mostly once debugged. Assumes good data already saved in device.
// Config Portal data input will be override DEFAULT_CONFIG_DATA
bool LOAD_DEFAULT_CONFIG_DATA = false;


ESP8266_AT_Configuration defaultConfig =
{
  //char header[16], dummy, not used
  "SHD_ESP8266",
  // WiFi_Credentials  WiFi_Creds  [NUM_WIFI_CREDENTIALS];
  // WiFi_Credentials.wifi_ssid and WiFi_Credentials.wifi_pw
  "SSID1",  "password1",
  "SSID2",  "password2",
  //char board_name     [24];
  "nRF52-ESP_AT",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

ESP8266_AT_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////


#endif    //Credentials_h
```

#### 4. File [dynamicParams.h](examples/nRF52_ESP8266Shield/dynamicParams.h)

```cpp
#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

#define USE_DYNAMIC_PARAMETERS      true

/////////////// Start dynamic Credentials ///////////////

//Defined in <Esp8266_AT_WM_Lite_nRF52.h>
/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

#define MAX_MQTT_SERVER_LEN      34
char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "mqtt-server";

#define MAX_MQTT_PORT_LEN        6
char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";


MenuItem myMenuItems [] =
{
  { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
  { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
};

// Due to notorious 2K buffer limitation of ESO8266-AT shield, the NUM_MENU_ITEMS is limited to max 3
// to avoid WebServer not working due to HTML data larger than 2K can't be sent successfully
// The items with index larger than 3 will be ignored

uint16_t NUM_MENU_ITEMS = min( 3, sizeof(myMenuItems) / sizeof(MenuItem));  //MenuItemSize;

#else

MenuItem myMenuItems [] = {};

uint16_t NUM_MENU_ITEMS = 0;
#endif

/////// // End dynamic Credentials ///////////


#endif      //dynamicParams_h
```
---

This is the terminal output when running [nRF52_ESP8266Shield](examples/nRF52_ESP8266Shield) example on ***Adafruit ItsyBitsy NRF52840 Express*** and DRD is detected:

1. Open Config Portal

```
Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY_EXPRESS
[ESP_AT] Use ES8266-AT Command
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
*AT: Double Reset Detected
*AT: ======= Start Default Config Data =======
*AT: Hdr=SHD_ESP8266,SSID=SSID1,PW=password1
*AT: SSID1=SSID2,PW1=password2
*AT: BName=nRF52-ESP_AT
*AT: LoadCfgFile 
*AT: OK
*AT: LoadCredFile 
*AT: ChkCrR: Buffer allocated, Sz=35
*AT: ChkCrR:pdata=mqtt-server,len=34
*AT: ChkCrR:pdata=1883,len=6
*AT: OK
*AT: CrCCsum=0x55e,CrRCsum=0x55e
*AT: Buffer freed
*AT: CCSum=0x1030,RCSum=0x1030
*AT: LoadCredFile 
*AT: CrR:pdata=mqtt-server,len=34
*AT: CrR:pdata=1883,len=6
*AT: OK
*AT: CrCCsum=0x55e,CrRCsum=0x55e
*AT: Valid Stored Dynamic Data
*AT: ======= Start Stored Config Data =======
*AT: Hdr=SHD_ESP8266,SSID=HueNet1,PW=****
*AT: SSID1=HueNet2,PW1=jenni****qqs
*AT: BName=nRF52
*AT: b:StayInCfgPortal:DRD
*AT: SSID=CfgPrtl-SSID,PW=CfgPrtl-PW
*AT: IP=192.168.4.1,CH=1
F
Stored Dynamic Params:
MQTT Server = mqtt-server
Port = 1883
FFFF
```

2. Got valid Credential from Config Portal, then connected to WiFi

```
Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY_EXPRESS
[ESP_AT] Use ES8266-AT Command
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
*AT: ======= Start Default Config Data =======
*AT: Hdr=SHD_ESP8266,SSID=SSID1,PW=password1
*AT: SSID1=SSID2,PW1=password2
*AT: BName=nRF52-ESP_AT
*AT: LoadCfgFile 
*AT: OK
*AT: LoadCredFile 
*AT: ChkCrR: Buffer allocated, Sz=35
*AT: ChkCrR:pdata=mqtt-server,len=34
*AT: ChkCrR:pdata=1883,len=6
*AT: OK
*AT: CrCCsum=0x55e,CrRCsum=0x55e
*AT: Buffer freed
*AT: CCSum=0x1030,RCSum=0x1030
*AT: LoadCredFile 
*AT: CrR:pdata=mqtt-server,len=34
*AT: CrR:pdata=1883,len=6
*AT: OK
*AT: CrCCsum=0x55e,CrRCsum=0x55e
*AT: Valid Stored Dynamic Data
*AT: ======= Start Stored Config Data =======
*AT: Hdr=SHD_ESP8266,SSID=HueNet1,PW=****
*AT: SSID1=HueNet2,PW1=****
*AT: BName=nRF52
*AT: ConMultiWifi
*AT: con2WF:SSID=HueNet1,PW=****
*AT: Remaining retry_time=3
*AT: WOK, lastConnectedIndex=0
*AT: con2WF:OK
*AT: IP=192.168.2.43
*AT: b:WOK
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
H
Stored Dynamic Params:
MQTT Server = mqtt-server
Port = 1883
HHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH

```

3. Normal operation. Losing Primary WiFi AP and auto(re)connect to Secondary WiFi AP

```

Start nRF52_ESP8266Shield on NRF52840_ITSYBITSY_EXPRESS
[ESP_AT] Use ES8266-AT Command
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
*AT: ======= Start Default Config Data =======
*AT: Hdr=SHD_ESP8266,SSID=SSID1,PW=password1
*AT: SSID1=SSID2,PW1=password2
*AT: BName=nRF52-ESP_AT
*AT: LoadCfgFile 
*AT: OK
*AT: LoadCredFile 
*AT: ChkCrR: Buffer allocated, Sz=35
*AT: ChkCrR:pdata=mqtt-server,len=34
*AT: ChkCrR:pdata=1883,len=6
*AT: OK
*AT: CrCCsum=0x55e,CrRCsum=0x55e
*AT: Buffer freed
*AT: CCSum=0x1030,RCSum=0x1030
*AT: LoadCredFile 
*AT: CrR:pdata=mqtt-server,len=34
*AT: CrR:pdata=1883,len=6
*AT: OK
*AT: CrCCsum=0x55e,CrRCsum=0x55e
*AT: Valid Stored Dynamic Data
*AT: ======= Start Stored Config Data =======
*AT: Hdr=SHD_ESP8266,SSID=HueNet1,PW=****
*AT: SSID1=HueNet2,PW1=****
*AT: BName=nRF52
*AT: ConMultiWifi
*AT: con2WF:SSID=HueNet1,PW=****
*AT: Remaining retry_time=3
*AT: WOK, lastConnectedIndex=0     <== Connected to Primary WiFi AP
*AT: con2WF:OK
*AT: IP=192.168.2.43
*AT: b:WOK
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
H
Stored Dynamic Params:
MQTT Server = mqtt-server
Port = 1883
HHHHHHHHH HHHHHHHHHH
*AT: r:Check&WLost
*AT: r:WLost.ReconW                 <== Lost Primary WiFi AP
*AT: ConMultiWifi
*AT: Using index=1, lastConnectedIndex=0
*AT: con2WF:SSID=HueNet2,PW=****
*AT: Remaining retry_time=2
*AT: WOK, lastConnectedIndex=1     <== Reconnect to Secondary WiFi AP
*AT: con2WF:OK
*AT: IP=192.168.2.43
*AT: r:WOK
HHHHH
```

---

#### Debug
Debug is enabled by default on Serial. To disable, add at the beginning of sketch

```cpp
/* Comment this out to disable prints and save space */
#define DRD_GENERIC_DEBUG             true

/* Comment this out to disable prints and save space */
#define ESP_AT_DEBUG_OUTPUT           Serial
#define _ESP_AT_LOGLEVEL_             1

#define ESP_AT_DEBUG    true
```
---

## Troubleshooting
If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `ESP8266 AT shield` AT-command or this library version.

Sometimes, the library will only work if you update the `ESP8266 AT shield` core to the newer or older version because some function compatibility.

### TO DO

1. Too many things to list, EEPROM, SPIFFS/FS/FAT FS (if available). Done.
2. Find better and easier way to add more parameters. Done.
3. Add more examples. Done.
4. Add more boards. Done.

---

### New Version v1.0.4

1. Add support to ***ESP32-AT WiFi shields.***
2. Add support to ***WIS600-01S/W600-AT WiFi shields.***
3. Modify LOAD_DEFAULT_CONFIG_DATA logic.
4. Enhance MultiWiFi connection logic. 
5. Fix WiFi Status bug.

### New Version v1.0.3

1. Add support to ***nRF52 (AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.)**. Dynamic custom parameters to be saved ***automatically in LittleFS***.
2. Add MultiWiFi features for WiFi
3. Add DoubleResetDetector (DRD) feature.
4. Restructure examples separate Credentials / Defines / Dynamic Params / Code.
5. Drop support to Teensy boards.

### New Version v1.0.2

1. Add support to ***SAM51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.) and SAM DUE***.
2. WiFi Password max length is 63, according to WPA2 standard.
3. Permit to input special chars such as ***~,!,@,#,$,%,^,*,&*** into data fields.
4. Fix bug

#### New in v1.0.1

1. New ***powerful-yet-simple-to-use feature to enable adding dynamic custom parameters*** from sketch and input using the same Config Portal. Config Portal will be auto-adjusted to match the number of dynamic parameters.
2. Dynamic custom parameters to be saved ***automatically in EEPROM, SAMD EEPROM-emulated FlashStorage or SAM DUE DueFlashStorage***.

#### New in v1.0.0

1. This is a Light-Weight Credentials / WiFi Connection Manager with fallback web configuration portal. Completely new to support ***Teensy, SAM DUE, SAMD, STM32, etc. boards running ESP8266 AT-command shields.*** with small memory (64+K bytes)
2. Config Portal AP SSID and Password will use 4 bytes of hardware unique macAddress, only for Teensy.

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### Copyright

Copyright 2020- Khoi Hoang


