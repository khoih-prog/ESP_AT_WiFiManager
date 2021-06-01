/********************************************************************************************************************************
  ESP_AT_WiFiManager-impl_SAMD.h
  WiFi/Credentials Manager for SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` shields

  ESP_AT_WiFiManager is a library for the Teensy, SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` shields
  (https://github.com/esp8266/Arduino) to enable easy configuration and reconfiguration of WiFi, etc. credentials using a Captive Portal

  Inspired by:
  http://www.esp8266.com/viewtopic.php?f=29&t=2520
  https://github.com/chriscook8/esp-arduino-apboot
  https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/examples/CaptivePortalAdvanced/

  Based on and modified from Tzapu https://github.com/tzapu/WiFiManager
  and from Ken Taylor https://github.com/kentaylor

  Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_WiFiManager
  Licensed under MIT license
  Version: 1.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      08/03/2020 Initial coding
  1.0.1   K Hoang      22/06/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, NINA_B302_ublox, etc.
  1.0.2   K Hoang      02/07/2020 Add support to ESP32-AT-command shields.
  1.0.3   K Hoang      28/07/2020 Add support to STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards. Add Packages' Patches.
  1.1.0   K Hoang      27/04/2021 Use new FlashStorage_STM32 library. Add support to new STM32 core v2.0.0 and STM32L5
  1.2.0   K Hoang      12/05/2021 Add support to RASPBERRY_PI_PICO using Arduino-pico core
  1.3.0   K Hoang      28/05/2021 Add support to Nano_RP2040_Connect, RASPBERRY_PI_PICO using RP2040 Arduino mbed core
 *********************************************************************************************************************************/

#ifndef ESP_AT_WiFiManager_impl_SAMD_h
#define ESP_AT_WiFiManager_impl_SAMD_h

#define DEFAULT_HOST_NAME     "SAMD"

//https://github.com/khoih-prog/FlashStorage_SAMD
#include <FlashStorage_SAMD.h>
FlashStorage(ESP_AT_WM_Config_data, ESP_AT_WM_Configuration);

void ESP_AT_WiFiManager::resetBoard()
{
  NVIC_SystemReset();
}
  
void ESP_AT_WiFiManager::clearConfigData()
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  ESP_AT_WM_Config_data.write(ESP_AT_WM_Config);
}

bool ESP_AT_WiFiManager::getConfigData()
{
  hadConfigData = false;
  
  ESP_AT_WM_Config = ESP_AT_WM_Config_data.read();
  
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
    strcpy(ESP_AT_WM_Config.host_name,        DEFAULT_HOST_NAME);
    // Don't need
    ESP_AT_WM_Config.checkSum = 0;

    ESP_AT_WM_Config_data.write(ESP_AT_WM_Config);

    return false;
  }
  else if ( !strncmp(ESP_AT_WM_Config.wifi_ssid,   ESP_AT_NO_CONFIG, strlen(ESP_AT_NO_CONFIG))   ||
            !strncmp(ESP_AT_WM_Config.wifi_pw,     ESP_AT_NO_CONFIG, strlen(ESP_AT_NO_CONFIG) ) )
  {
    // If SSID, PW ="blank", return false
    return false;
  }
  else
  {
    DEBUG_WM1(F("======= Start Stored Config Data ======="));
    displayConfigData();
  }
  
  // If "blank" or NULL, set false flag and exit
  if (!isWiFiConfigValid())
  {
    return false;
  }

  hadConfigData = true;
  
  return true;
}

void ESP_AT_WiFiManager::saveConfigData()
{
  int calChecksum = calcChecksum();
  ESP_AT_WM_Config.checkSum = calChecksum;
  
  DEBUG_WM2(F("SaveFlash,CSum="), calChecksum);

  ESP_AT_WM_Config_data.write(ESP_AT_WM_Config);
}
    
#endif      //ESP_AT_WiFiManager_impl_SAMD_h
