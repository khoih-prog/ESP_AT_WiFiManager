/****************************************************************************************************************************
   ESP_AT_WiFiManager-impl_STM32.h
   WiFi/Credentials Manager for SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` shields

   ESP_AT_WiFiManager is a library for the Teensy, SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` shields
   (https://github.com/esp8266/Arduino) to enable easy configuration and reconfiguration of WiFi, etc. credentials using a Captive Portal
   
   Based on and modified from Tzapu https://github.com/tzapu/WiFiManager
   and from Ken Taylor https://github.com/kentaylor

   Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_WiFiManager
   Licensed under MIT license
   Version: 1.0.3

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      08/03/2020 Initial coding
    1.0.1   K Hoang      22/06/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, NINA_B302_ublox, etc.
    1.0.2   K Hoang      02/07/2020 Add support to ESP32-AT-command shields.
    1.0.3   K Hoang      28/07/2020 Add support to STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards. Add Packages' Patches.
 *****************************************************************************************************************************/

#ifndef ESP_AT_WiFiManager_impl_STM32_h
#define ESP_AT_WiFiManager_impl_STM32_h

#include <EEPROM.h>

void ESP_AT_WiFiManager::resetBoard(void)
{
  void(*resetFunc)(void) = 0;
  resetFunc();
}

void ESP_AT_WiFiManager::clearConfigData(void)
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  saveConfigData();
}

bool ESP_AT_WiFiManager::getConfigData(void)
{
  hadConfigData = false;
  
  EEPROM.begin();
  DEBUG_WM2(F("EEPROMsz:"), EEPROM_SIZE);
  EEPROM.get(EEPROM_START, ESP_AT_WM_Config);

  int calChecksum = calcChecksum();
  
  DEBUG_WM4(F("CCSum=0x"), String(calChecksum, HEX), F(",RCSum=0x"), String(ESP_AT_WM_Config.checkSum, HEX));

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
  
  DEBUG_WM2(F("SaveEEPROM,CSum="), calChecksum);

  EEPROM.put(EEPROM_START, ESP_AT_WM_Config);
}
    
#endif      //ESP_AT_WiFiManager_impl_STM32_h


