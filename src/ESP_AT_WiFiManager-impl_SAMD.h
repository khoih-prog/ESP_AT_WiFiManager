/****************************************************************************************************************************
 * ESP_AT_WiFiManager-impl_SAMD.h
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

#ifndef ESP_AT_WiFiManager_impl_SAMD_h
#define ESP_AT_WiFiManager_impl_SAMD_h

void ESP_AT_WiFiManager::clearConfigData(void)
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  ESP_AT_WM_Config_data.write(ESP_AT_WM_Config);
}

bool ESP_AT_WiFiManager::getConfigData(void)
{
  hadConfigData = false;
  
  ESP_AT_WM_Config = ESP_AT_WM_Config_data.read();

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

    ESP_AT_WM_Config_data.write(ESP_AT_WM_Config);

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

  ESP_AT_WM_Config_data.write(ESP_AT_WM_Config);
}
    
#endif      //ESP_AT_WiFiManager_impl_SAMD_h
