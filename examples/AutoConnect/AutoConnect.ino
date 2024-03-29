/****************************************************************************************************************************
  AutoConnect.ino
  WiFi/Credentials Manager for SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` shields

  ESP_AT_WiFiManager is a library for the Teensy, SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` shields
  (https://github.com/esp8266/Arduino) to enable easy configuration and reconfiguration of WiFi, etc. credentials using a Captive Portal

  Based on and modified from Tzapu https://github.com/tzapu/WiFiManager
  and from Ken Taylor https://github.com/kentaylor

  Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_WiFiManager
  Licensed under MIT license
 *****************************************************************************************************************************/
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
  static ulong checkstatus_timeout = 0;

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

  // 0 for random channel
  //ESP_AT_wiFiManager.setAPChannel(0);
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

  // Get Router SSID and PASS from EEPROM, then open Config portal AP named "ESP_AT_XXXXXX_AutoConnectAP" and PW "ESP_AT_PW"
  // 1) If got stored Credentials, Config portal timeout is 60s
  // 2) If no stored Credentials, stay in Config portal until get WiFi Credentials
  if (!ESP_AT_wiFiManager.autoConnect(ssid.c_str(), password))
  {
    Serial.println("failed to connect and hit timeout");
    delay(1000);
  }
}

void setup()
{
  // put your setup code here, to run once:
  // initialize the LED digital pin as an output.
  pinMode(LOCAL_PIN_LED, OUTPUT);

  // turn the LED on by making the voltage LOW to tell us we are in configuration mode.
  digitalWrite(LOCAL_PIN_LED, LED_ON); 

  Serial.begin(115200);

  while (!Serial && millis() < 5000);

#if USE_ESP32_AT
  Serial.println("\nStart AutoConnect with ESP32-AT WiFi module on " + String(BOARD_NAME));
#else
  Serial.println("\nStart AutoConnect with ESP8266-AT WiFi module on " + String(BOARD_NAME));
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

  //if you get here you have exied from Config Portal
  Serial.println("Exit Config Portal");
}

void loop()
{
  // put your main code here, to run repeatedly
  check_status();
}
