/****************************************************************************************************************************
   ESP_AT_WiFiManager-impl_nRF52.h
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

#ifndef ESP_AT_WiFiManager_impl_nRF52_h
#define ESP_AT_WiFiManager_impl_nRF52_h

//Use LittleFS for nRF52
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

using namespace Adafruit_LittleFS_Namespace;
File file(InternalFS);

// Use LittleFS/InternalFS for nRF52
#define  CONFIG_FILENAME              ("/wm_config.dat")
#define  CONFIG_FILENAME_BACKUP       ("/wm_config.bak")

void ESP_AT_WiFiManager::resetBoard(void)
{
  delay(1000);
  // Restart for nRF52
  NVIC_SystemReset();
}

void ESP_AT_WiFiManager::clearConfigData(void)
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  
  saveConfigData();
}

void ESP_AT_WiFiManager::loadConfigData(void)
{
  DEBUG_WM1(F("LoadCfgFile "));
  
  // file existed
  file.open(CONFIG_FILENAME, FILE_O_READ);      
  if (!file)
  {
    DEBUG_WM1(F("failed"));

    // Trying open redundant config file
    file.open(CONFIG_FILENAME_BACKUP, FILE_O_READ);
    DEBUG_WM1(F("LoadBkUpCfgFile "));

    if (!file)
    {
      DEBUG_WM1(F("failed"));
      return;
    }
  }
 
  file.seek(0);
  file.read((char *) &ESP_AT_WM_Config, sizeof(ESP_AT_WM_Config));

  DEBUG_WM1(F("OK"));
  file.close();
}
    
bool ESP_AT_WiFiManager::getConfigData(void)
{
  hadConfigData = false;
  
  // Initialize Internal File System
  if (!InternalFS.begin())
  {
    DEBUG_WM1(F("InternalFS failed"));
    return false;
  }
  
  // if config file exists, load
  loadConfigData();   
  DEBUG_WM1(F("======= Start Stored Config Data ======="));
  displayConfigData();    

  int calChecksum = calcChecksum();

  DEBUG_WM4(F("CCSum=0x"), String(calChecksum, HEX), F(",RCSum=0x"), String(ESP_AT_WM_Config.checkSum, HEX));


  if ( (strncmp(ESP_AT_WM_Config.header, ESP_AT_BOARD_TYPE, strlen(ESP_AT_BOARD_TYPE)) != 0) ||
       (calChecksum != ESP_AT_WM_Config.checkSum) )
  {
    // Including Credentials CSum
    DEBUG_WM2(F("InitCfgFile,sz="), sizeof(ESP_AT_WM_Config));
        
    memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));

    // doesn't have any configuration
    strcpy(ESP_AT_WM_Config.header,           ESP_AT_BOARD_TYPE);
    strcpy(ESP_AT_WM_Config.wifi_ssid,        ESP_AT_NO_CONFIG);
    strcpy(ESP_AT_WM_Config.wifi_pw,          ESP_AT_NO_CONFIG);
    strcpy(ESP_AT_WM_Config.host_name,        ESP_AT_NO_CONFIG);
    // Don't need
    ESP_AT_WM_Config.checkSum = 0;

    saveConfigData();

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
  DEBUG_WM1(F("SaveCfgFile "));

  int calChecksum = calcChecksum();
  ESP_AT_WM_Config.checkSum = calChecksum;
  
  DEBUG_WM2(F("WCSum=0x"), String(calChecksum, HEX));

  file.open(CONFIG_FILENAME, FILE_O_WRITE);

  if (file)
  {
    file.seek(0);
    file.write((uint8_t*) &ESP_AT_WM_Config, sizeof(ESP_AT_WM_Config));
    
    file.close();
    DEBUG_WM1(F("OK"));
  }
  else
  {
    DEBUG_WM1(F("failed"));
  }

  DEBUG_WM1(F("SaveBkUpCfgFile "));

  // Trying open redundant Auth file
  file.open(CONFIG_FILENAME_BACKUP, FILE_O_WRITE);

  if (file)
  {
    file.seek(0);
    file.write((uint8_t *) &ESP_AT_WM_Config, sizeof(ESP_AT_WM_Config));
    
    file.close();
    DEBUG_WM1(F("OK"));
  }
  else
  {
    DEBUG_WM1(F("failed"));
  } 
}
    
#endif      //ESP_AT_WiFiManager_impl_nRF52_h
