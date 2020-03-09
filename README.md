# ESP_AT_WiFiManager

[![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WiFiManager.svg?)](https://www.ardu-badge.com/ESP_AT_WiFiManager)

This library is based on, modified, bug-fixed and improved from:

1. [`Tzapu WiFiManager`](https://github.com/tzapu/WiFiManager)
2. [`Ken Taylor WiFiManager`](https://github.com/kentaylor/WiFiManager)

to support ***Teensy, SAM DUE, SAMD, STM32, etc. boards running ESP8266 AT-command shields.***

The AVR-family boards (Mega, UNO, Nano, etc.) are ***not supported*** as they don't have enough memory to run Config Portal WebServer.

This is a Credentials / WiFi Connection Manager with fallback web configuration portal.

The web configuration portal, served from the `ESP8266 AT-command shields` is operating as an access point (AP) with configurable static IP address or use default IP Address of 192.168.4.1

The configuration portal is captive, so it will present the configuration dialogue regardless of the web address selected, excluding https requests.

## Prerequisite
1. [`Arduino IDE 1.8.12 or later` for Arduino](https://www.arduino.cc/en/Main/Software)
2. [`Arduino Core for STM32 v1.8.0 or later`](https://github.com/khoih-prog/Arduino_Core_STM32) for STM32 boards
3. [`Teensy core 1.51 or later`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards
4. [`ESP8266_AT_WebServer library`](https://github.com/khoih-prog/ESP8266_AT_WebServer)
5. [`FlashStorage library`](https://github.com/khoih-prog/FlashStorage) for SAMD boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)
6. [`DueFlashStorage library`](https://github.com/sebnil/DueFlashStorage) for SAM DUE



## How It Works

- The [ConfigOnSwitch](examples/ConfigOnSwitch) example shows how it works and should be used as the basis for a sketch that uses this library.
- The concept of ConfigOnSwitch is that a new `ESP8266 AT shield` will start a WiFi configuration portal when powered up and save the configuration data in host's non-volatile memory. Thereafter, the configuration portal will only be started again if a button is pushed on the host board.
- Using any WiFi enabled device with a browser (computer, phone, tablet) connect to the newly created AP and type in the AP IP address (default 192.168.4.1).
- Choose one of the 3 best APs scanned, enter password, click `Save`.
- `ESP8266 AT shield` will try to connect. If successful, the dynamic DHCP or configured static IP address will be displayed in the configuration portal. 
- The `ESP8266 AT shield` WiFi Config Portal network and Web Server will shutdown to return control to the sketch code.

## Quick Start

The best and easiest way is to use `Arduino Library Manager`. Search for `ESP_AT_WiFiManager`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_WiFiManager.svg?)](https://www.ardu-badge.com/ESP_AT_WiFiManager) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [ESP_AT_WiFiManager](https://github.com/khoih-prog/ESP_AT_WiFiManager) page.
2. Download the latest release `ESP_AT_WiFiManager-master.zip`.
3. Extract the zip file to `ESP_AT_WiFiManager-master` directory 
4. Copy whole `ESP_AT_WiFiManager-master/src` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.


### Using
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

- When you want to open a config portal, just add

```cpp
ESP_AT_WiFiManager ESP_AT_wiFiManager;
```

- To not use default AP WiFi Channel 10 to avoid conflict with other WiFi APs, call 
```cpp
ESP_AT_wiFiManager.setAPChannel(newChannel);
```

- To use static IP (not the default dynamically allocated DHCP IP) from the network to be connected, call 
```cpp
ESP_AT_wiFiManager.setSTAStaticIPConfig(IPAddress(xxx,xxx,xxx,xxx));
```

- To use different static AP IP (not use default `192.168.4.1`), call 
```cpp
ESP_AT_wiFiManager.setAPStaticIPConfig(IPAddress(xxx,xxx,xxx,xxx));
```

- To use default AP SSID `ESP_AT_XXXXXX`, later call 

```cpp
ESP_AT_wiFiManager.startConfigPortal()
```

- To use personalized SSID /  Password, call

```cpp
ESP_AT_wiFiManager.startConfigPortal((const char *) ssid.c_str(), password);
```

While in AP mode, connect to it using its `SSID` (ESP_AT_XXXXXX) / `Password` ("ESP_AT_PW"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then save. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


OnceCredentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.


Also see examples: 
 1. [ConfigOnSwitch](examples/ConfigOnSwitch)
 2. [ConfigOnStartup](examples/ConfigOnStartup) 
 3. [AutoConnect](examples/AutoConnect)
 4. [AutoConnectWithFeedback](examples/AutoConnectWithFeedback)

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

## Documentation

#### Password protect the configuration Access Point
You can password protect the configuration AP.  Simply add an SSID as the first parameter and the password as a second parameter to `startConfigPortal` as follows:

```cpp
ESP_AT_wiFiManager.startConfigPortal(SSID , password);
```

Use Password having 8+ characters.

The guidelines are that a wifi password must consist of 8 to 63 ASCII-encoded characters in the range of 32 to 126 (decimal)


#### Configuration Portal Timeout
You can set a timeout(in seconds) so that `ESP8266 AT shield` doesn't hang waiting to be configured for ever. 

```cpp
ESP_AT_WiFiManager.setConfigPortalTimeout(60);
```
which will wait 1 minutes (60 seconds). 

When the time passes, the startConfigPortal function will return and continue the sketch, unless you're accessing the Config Portal. In this case, the `startConfigPortal` function will stay until you save config data or exit the Config Portal.


#### On Demand Configuration Portal

Sample Code

```cpp
#define _ESP_AT_LOGLEVEL_   0
#define DEBUG_WIFIMGR       true  //false

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) )
  #if defined(ESP8266_AT_USE_STM32)
  #undef ESP8266_AT_USE_STM32
  #endif
  #define ESP8266_AT_USE_STM32      true
#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ESP8266_AT_USE_SAM_DUE)
  #undef ESP8266_AT_USE_SAM_DUE
  #endif
  #define ESP8266_AT_USE_SAM_DUE      true
#endif

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
   || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
   || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) )       
  #if defined(ESP8266_AT_USE_SAMD)
    #undef ESP8266_AT_USE_SAMD
  #endif
  #define ESP8266_AT_USE_SAMD      true
#endif

#ifdef CORE_TEENSY
  // For Teensy 4.0
  #define EspSerial Serial2   //Serial2, Pin RX2 : 7, TX2 : 8
  #if defined(__IMXRT1062__)
  #define BOARD_TYPE      "TEENSY 4.0"
  #elif ( defined(__MKL26Z64__) || defined(ARDUINO_ARCH_AVR) )
  #define BOARD_TYPE      "TEENSY LC or 2.0"
  #else
  #define BOARD_TYPE      "TEENSY 3.X"
  #endif

#elif (ESP8266_AT_USE_SAMD) 
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
  #elif ( defined(__SAM3X8E__) || (__SAM3X8E__) || (__CPU_ARC__) )
    #define BOARD_TYPE      "SAMD Board"
  #else
    #define BOARD_TYPE      "SAMD Unknown"
  #endif

#elif (ESP8266_AT_USE_SAM_DUE) 
// For SAM DUE
  #define EspSerial Serial1
  #define BOARD_TYPE      "SAM DUE" 
  
#elif (ESP8266_AT_USE_STM32) 
// For STM32F
  #define EspSerial Serial1
  #define BOARD_TYPE      "STM32F"  
#else
// For other boards. Change Serial as necessary
#define EspSerial Serial3
#define BOARD_TYPE      "Unknown"
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

IPAddress staticAP_IP = IPAddress(192,168,100,1);

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;

// Onboard LED I/O pin on board
const int LOCAL_PIN_LED = 13; // Pin 13, Controls the onboard LED.

#define LED_ON    HIGH
#define LED_OFF   LOW

void heartBeatPrint(void)
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

  //KH
  #define HEARTBEAT_INTERVAL    10000L
  // Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + HEARTBEAT_INTERVAL;
  }
}

void enterConfigPortal(void)
{
  //Local intialization. Once its business is done, there is no need to keep it around
  ESP_AT_WiFiManager ESP_AT_wiFiManager;

  ESP_AT_wiFiManager.setDebugOutput(true);
   
  ESP_AT_wiFiManager.setMinimumSignalQuality(-1);

  ESP_AT_wiFiManager.setAPChannel(1);

  // Default AP IP is 192.168.4.1. Uncomment to use different AP IP
  ESP_AT_wiFiManager.setAPStaticIPConfig(staticAP_IP);
  
  // Set static STA IP
  ESP_AT_wiFiManager.setSTAStaticIPConfig(IPAddress(192,168,2,114));  
  
  //Check if there is stored WiFi router/password credentials.
  //If not found, device will remain in configuration mode until switched off via webserver.
  Serial.print("Opening Config Portal. ");
  
  Router_SSID = ESP_AT_wiFiManager.WiFi_SSID();
  Router_Pass = ESP_AT_wiFiManager.WiFi_Pass();
  
  if (Router_SSID != "")
  {
    ESP_AT_wiFiManager.setConfigPortalTimeout(60); //If no access point name has been previously entered disable timeout.
    Serial.println(F("Got stored Credentials. Timeout 60s"));
  }
  else
    Serial.println(F("No stored Credentials. No timeout"));
      
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
  pinMode(LOCAL_PIN_LED, OUTPUT);
  digitalWrite(LOCAL_PIN_LED, LED_ON); // turn the LED on by making the voltage LOW to tell us we are in configuration mode.
  
  Serial.begin(115200);
  
  unsigned long startedAt = millis();
  delay(200);
  Serial.println("\nStart ConfigOnStartup on " + String(BOARD_TYPE));

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
    while((!WiFi.status() || WiFi.status() >= WL_DISCONNECTED) && i++ < WHILE_LOOP_STEPS)
    {
      delay(WHILE_LOOP_DELAY);
    }    
  }
  
  Serial.print(F("After waiting "));
  Serial.print((millis()- startedAt) / 1000);
  Serial.print(F(" secs in setup(), connect result is "));

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print(F("connected. Local IP: "));
    Serial.println(WiFi.localIP());
  }
}


void loop() 
{
  // put your main code here, to run repeatedly
  check_status();
}
```

This is the terminal output when running [ConfigOnSwitch](examples/ConfigOnSwitch) example on ***Teensy 4.0***:

```
Start ConfigOnSwitch on TEENSY 4.0
Opening Config Portal. *WM: Header = ESP_AT, SSID = ****, PW = ****
*WM: Host Name = nothing
Got stored Credentials. Timeout 60s
Start Config Portal, SSID = ESP_AT_1ABCDEF, Pass = ESP_AT_PW
*WM: Configure AP: ESP_AT_1ABCDEF
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
*WM: HueNet / -28
*WM: HueNet1 / -41
*WM: HueNet2 / -59
*WM: Sent config page
*WM: WiFi save
*WM: Sent wifisave page
*WM: Connect to new AP
*WM: Connect wifi with new params
*WM: Data cleared
*WM: Static IP : 192.168.2.114
*WM: Connect result: WL_CONNECTED
WiFi connected...yeey
After waiting 0 secs in setup(), connect result is connected. Local IP: 192.168.2.114
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH
```

#### Custom Parameters
Many applications need configuration parameters like `MQTT host and port`, [Blynk](http://www.blynk.cc) or [emoncms](http://emoncms.org) tokens, etc. While it is possible to use `ESP_AT_WiFiManager` to collect additional parameters it is better to read these parameters from a web service once `ESP_AT_WiFiManager` has been used to connect to the internet. This makes `ESP_AT_WiFiManager` simple to code and use, parameters can be edited on a regular web server and can be changed remotely after deployment.


#### Custom IP Configuration
You can set a custom IP for both AP (access point, config mode) and STA (station mode, client mode, normal project state)

##### Custom Access Point IP Configuration
This will set your captive portal to a specific IP should you need/want such a feature. Add the following snippet before `startConfigPortal()`
```cpp
// Default AP IP is 192.168.4.1. Uncomment to use different AP IP
ESP_AT_wiFiManager.setAPStaticIPConfig(IPAddress(192,168,100,1));
```

##### Custom Station (client) Static IP Configuration
This will use the specified IP configuration instead of using DHCP in station mode.
```cpp
// Set static STA IP
ESP_AT_wiFiManager.setSTAStaticIPConfig(IPAddress(192,168,2,114));
```

#### Custom HTML, CSS, Javascript
There are various ways in which you can inject custom HTML, CSS or Javascript into the configuration portal.
The options are:
- inject custom head element
You can use this to any html bit to the head of the configuration portal. If you add a `<style>` element, bare in mind it overwrites the included css, not replaces.

```cpp
ESP_AT_wiFiManager.setCustomHeadElement("<style>html{filter: invert(100%); -webkit-filter: invert(100%);}</style>");
```

- inject a custom bit of html in the configuration form

```cpp
ESP_AT_WMParameter custom_text("<p>This is just a text paragraph</p>");
ESP_AT_wiFiManager.addParameter(&custom_text);
```

- inject a custom bit of html in a configuration form element
Just add the bit you want added as the last parameter to the custom parameter constructor.

```cpp
ESP_AT_WMParameter custom_mqtt_server("server", "mqtt server", "iot.eclipse", 40, " readonly");
```

#### Filter Networks
You can filter networks based on signal quality and show/hide duplicate networks.

- If you would like to filter low signal quality networks you can tell WiFiManager to not show networks below an arbitrary quality %;

```cpp
ESP_AT_wiFiManager.setMinimumSignalQuality(10);
```
will not show networks under 10% signal quality. If you omit the parameter it defaults to 8%;

- You can also remove or show duplicate networks (default is remove).
Use this function to show (or hide) all networks.

```cpp
ESP_AT_wiFiManager.setRemoveDuplicateAPs(false);
```

#### Debug
Debug is enabled by default on Serial. To disable, add before `startConfigPortal()`

```cpp
ESP_AT_wiFiManager.setDebugOutput(false);
```

## Troubleshooting
If you get compilation errors, more often than not, you may need to install a newer version of the board's core, `ESP8266 AT shield` AT-command or this library version.

Sometimes, the library will only work if you update the `ESP8266 AT shield` core to the newer or older version because some function compatibility.

### TO DO

1. Too many things to list, EEPROM, SPIFFS/FS/FAT FS (if available)
2. Find better and easier way to store/retrieve Credentials without using complicated ArduinoJson.
3. Find better and easier way to add more parameters.
4. Add more examples 

#### New in v1.0.0

- This is a Credentials / WiFi Connection Manager with fallback web configuration portal. Completely new to support ***Teensy, SAM DUE, SAMD, STM32, etc. boards running ESP8266 AT-command shields.***

### Contributions and thanks
1. Forked from [Tzapu](https://github.com/tzapu/WiFiManager) and [KenTaylor's version]( https://github.com/kentaylor/WiFiManager)

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

### Copyright

Copyright 2020- Khoi Hoang


