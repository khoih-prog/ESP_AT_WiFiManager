/****************************************************************************************************************************
 * ESP_AT_WiFiManager-impl_Teensy.h
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

#ifndef ESP_AT_WiFiManager_impl_Teensy_h
#define ESP_AT_WiFiManager_impl_Teensy_h

//KH
// Teensy 4.0 :  EEPROM_SIZE = 3824 = (255 * 15) - 1, why 1080 ???
// Teensy++2.0, 3.5 and 3.6 : EEPROM_SIZE = 4096
// Teensy++1.0, 3.0, 3.1 and 3.2 : EEPROM_SIZE = 2048
// Teensy2.0 : EEPROM_SIZE = 1024
// Teensy1.0 : EEPROM_SIZE = 512
// Teensy LC : EEPROM_SIZE = 128

/*
Teensy 4.0 => EEPROM_SIZE = 3824 = (255 * 15) - 1
#define FLASH_SECTORS  15
#if E2END > (255*FLASH_SECTORS-1)
#error "E2END is set larger than the maximum possible EEPROM size"
#endif
======================================================
Teensy3.x
#if defined(__MK20DX128__)      //Teensy 3.0
#define EEPROM_MAX  2048
#elif defined(__MK20DX256__)    //Teensy 3.1 and 3.2
#define EEPROM_MAX  2048
#elif defined(__MK64FX512__)    //Teensy 3.5
#define EEPROM_MAX  4096
#elif defined(__MK66FX1M0__)    //Teensy 3.6
#define EEPROM_MAX  4096
#elif defined(__MKL26Z64__)     //Teensy LC
#define EEPROM_MAX  255
#endif
======================================================
Teensy 2.x
Teensy 2.0
#if defined(__AVR_ATmega32U4__)     //Teensy 2.0
#elif defined(__AVR_AT90USB162__)   //Teensy 1.0
#elif defined(__AVR_AT90USB646__)   //Teensy++ 1.0
#elif defined(__AVR_AT90USB1286__)  //Teensy++ 2.0
*/

void ESP_AT_WiFiManager::clearConfigData(void)
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  EEPROM.put(EEPROM_START, ESP_AT_WM_Config);
}

bool ESP_AT_WiFiManager::getConfigData(void)
{
  hadConfigData = false;
  
  EEPROM.get(EEPROM_START, ESP_AT_WM_Config);

  int calChecksum = calcChecksum();

  if ( (strncmp(ESP_AT_WM_Config.header, ESP_AT_BOARD_TYPE, strlen(ESP_AT_BOARD_TYPE)) != 0) ||
       (calChecksum != ESP_AT_WM_Config.checkSum) )
  {
    memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));

    // doesn't have any configuration
    strcpy(ESP_AT_WM_Config.header,           ESP_AT_BOARD_TYPE);
    strcpy(ESP_AT_WM_Config.wifi_ssid,        ESP_AT_NO_CONFIG);
    strcpy(ESP_AT_WM_Config.wifi_pw,          ESP_AT_NO_CONFIG);
    strcpy(ESP_AT_WM_Config.host_name,        ESP_AT_NO_CONFIG);
    // Don't need
    ESP_AT_WM_Config.checkSum = 0;


    EEPROM.put(EEPROM_START, ESP_AT_WM_Config);

    return false;
  }
  else if ( !strncmp(ESP_AT_WM_Config.wifi_ssid,   ESP_AT_NO_CONFIG, strlen(ESP_AT_NO_CONFIG))   ||
            !strncmp(ESP_AT_WM_Config.wifi_pw,     ESP_AT_NO_CONFIG, strlen(ESP_AT_NO_CONFIG) ) )
  {
    // If SSID, PW ="nothing", return false
    return false;
  }
  else
  {
    displayConfigData();
  }

  hadConfigData = true;
  
  return true;
}

void ESP_AT_WiFiManager::saveConfigData(void)
{
  int calChecksum = calcChecksum();
  ESP_AT_WM_Config.checkSum = calChecksum;

  EEPROM.put(EEPROM_START, ESP_AT_WM_Config);
}
    
#endif      //ESP_AT_WiFiManager_impl_Teensy_h


