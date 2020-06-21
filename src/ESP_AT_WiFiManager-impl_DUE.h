/****************************************************************************************************************************
   ESP_AT_WiFiManager-impl_DUE.h
   WiFi/Credentials Manager for SAM DUE, SAMD, nRF52, STM32, etc. boards running `ESP8266/ESP32-AT-command` shields

   ESP_AT_WiFiManager is a library for the Teensy, SAM DUE, SAMD, nRF52, STM32, etc. boards running `ESP8266/ESP32-AT-command` shields
   (https://github.com/esp8266/Arduino) to enable easy configuration and reconfiguration of WiFi, etc. credentials using a Captive Portal
   
   Inspired by:
   http://www.esp8266.com/viewtopic.php?f=29&t=2520
   https://github.com/chriscook8/esp-arduino-apboot
   https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/

   Based on and modified from Tzapu https://github.com/tzapu/WiFiManager
   and from Ken Taylor https://github.com/kentaylor

   Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_WiFiManager
   Licensed under MIT license
   Version: 1.0.1

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
    1.0.0   K Hoang      08/03/2020 Initial coding
    1.0.1   K Hoang      22/06/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, NINA_B30_ublox, etc.
 *****************************************************************************************************************************/

#ifndef ESP_AT_WiFiManager_impl_DUE_h
#define ESP_AT_WiFiManager_impl_DUE_h

//Use DueFlashStorage to simulate EEPROM
//https://github.com/sebnil/DueFlashStorage
#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;

void ESP_AT_WiFiManager::resetBoard(void)
{
  rstc_start_software_reset(RSTC);
}

void ESP_AT_WiFiManager::clearConfigData(void)
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  dueFlashStorage.write(EEPROM_START, (byte *) &ESP_AT_WM_Config, sizeof(ESP_AT_WM_Config));
}

bool ESP_AT_WiFiManager::getConfigData(void)
{
  hadConfigData = false;
   
  ESP_AT_WM_Configuration* dataPointer = (ESP_AT_WM_Configuration* ) dueFlashStorage.readAddress(EEPROM_START);
  memcpy(&ESP_AT_WM_Config, dataPointer, sizeof(ESP_AT_WM_Config));

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
   
    dueFlashStorage.write(EEPROM_START, (byte *) &ESP_AT_WM_Config, sizeof(ESP_AT_WM_Config));

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
  
  DEBUG_WM2(F("SaveDueFlash, CSum="), calChecksum);
  
  dueFlashStorage.write(EEPROM_START, (byte *) &ESP_AT_WM_Config, sizeof(ESP_AT_WM_Config));
}
    
#endif    //ESP_AT_WiFiManager_impl_DUE_h


