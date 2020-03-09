/****************************************************************************************************************************
 * ConfigOnSwitch.ino
 * WiFi/Credentials Manager for Teensy, SAM DUE, SAMD, STM32, etc. boards running `ESP8266 AT-command` shields
 *
 * ESP_AT_WiFiManager is a library for the Teensy, SAM DUE, SAMD, STM32, etc. boards running `ESP8266 AT-command` shields
 * (https://github.com/esp8266/Arduino) to enable easy configuration and reconfiguration of WiFi, etc. credentials using a Captive Portal
 * inspired by:
 * http://www.esp8266.com/viewtopic.php?f=29&t=2520
 * https://github.com/chriscook8/esp-arduino-apboot
 * https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/
 *
 * Forked from Tzapu https://github.com/tzapu/WiFiManager
 * and from Ken Taylor https://github.com/kentaylor
 *
 * Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_WiFiManager
 * Licensed under MIT license
 * Version: 1.0.0
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      08/03/2020 Initial coding
 *****************************************************************************************************************************/
/****************************************************************************************************************************
 * This example will open a configuration portal when no WiFi configuration has been previously entered or when a button is pushed. 
 * It is the easiest scenario for configuration but requires a pin and a button on the device. 
 *
 * Also in this example a password is required to connect to the configuration portal 
 * network. This is inconvenient but means that only those who know the password or those 
 * already connected to the target WiFi network can access the configuration portal and 
 * the WiFi network credentials will be sent from the browser over an encrypted connection and
 * can not be read by observers.
 *****************************************************************************************************************************/
 
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

/* Trigger for inititating config mode is Pin D3 and also flash button on NodeMCU
 * Flash button is convenient to use but if it is pressed it will stuff up the serial port device driver 
 * until the computer is rebooted on windows machines.
 */
const int TRIGGER_PIN = 22;   // Change the PIN to whatever you'd like
/*
 * Alternative trigger pin. Needs to be connected to a button to use this pin. It must be a momentary connection
 * not connected permanently to ground. Either trigger pin will work.
 */
const int TRIGGER_PIN2 = 23; // Change the PIN to whatever you'd like

// Indicates whether ESP has WiFi credentials saved from previous session
bool initialConfig = false;

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
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(TRIGGER_PIN2, INPUT_PULLUP);
  pinMode(LOCAL_PIN_LED, OUTPUT);
  digitalWrite(LOCAL_PIN_LED, LED_ON); // turn the LED on by making the voltage LOW to tell us we are in configuration mode.
  
  Serial.begin(115200);
  
  unsigned long startedAt = millis();
  delay(200);
  Serial.println("\nStart ConfigOnSwitch on " + String(BOARD_TYPE));

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
  // is configuration portal requested?
  if ((digitalRead(TRIGGER_PIN) == LOW) || (digitalRead(TRIGGER_PIN2) == LOW)) 
  {
    Serial.println("\nConfig Portal requested.");   
    enterConfigPortal();
  }
   
  // put your main code here, to run repeatedly
  check_status();

}
