/********************************************************************************************************************************
  ESP_AT_WiFiManager-impl_STM32.h
  WiFi/Credentials Manager for SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` shields

  ESP_AT_WiFiManager is a library for the Teensy, SAM DUE, SAMD, nRF52, STM32F/L/H/G/WB/MP1, etc. boards running `ESP8266/ESP32-AT-command` 
  shields to enable easy configuration and reconfiguration of WiFi, etc. credentials using a Captive Portal

  Based on and modified from Tzapu https://github.com/tzapu/WiFiManager
  and from Ken Taylor https://github.com/kentaylor

  Built by Khoi Hoang https://github.com/khoih-prog/ESP_AT_WiFiManager
  Licensed under MIT license
  
  Version: 1.4.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      08/03/2020 Initial coding
  1.0.1   K Hoang      22/06/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, NINA_B302_ublox, etc.
  1.0.2   K Hoang      02/07/2020 Add support to ESP32-AT-command shields.
  1.0.3   K Hoang      28/07/2020 Add support to STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards. Add Packages' Patches.
  1.1.0   K Hoang      27/04/2021 Use new FlashStorage_STM32 library. Add support to new STM32 core v2.0.0 and STM32L5
  1.2.0   K Hoang      12/05/2021 Add support to RASPBERRY_PI_PICO using Arduino-pico core
  1.3.0   K Hoang      28/05/2021 Add support to Nano_RP2040_Connect, RASPBERRY_PI_PICO using RP2040 Arduino mbed core
  1.3.1   K Hoang      10/10/2021 Update `platform.ini` and `library.json`
  1.4.0   K Hoang      28/05/2021 Add support to WizNet WizFi360 such as WIZNET_WIZFI360_EVB_PICO using arduino-pico core
 ********************************************************************************************************************************/

#ifndef ESP_AT_WiFiManager_impl_STM32_h
#define ESP_AT_WiFiManager_impl_STM32_h

//////////////////////////////////////////////

#if !( defined(STM32F0) || defined(STM32F1)   || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1)   || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1)  || defined(STM32L5) )
  #error This code is intended to run on STM32F/L/H/G/WB/MP1 platform! Please check your Tools->Board setting.
#endif

//////////////////////////////////////////////

#define DEFAULT_HOST_NAME     "STM32"

#include <IWatchdog.h>

/////////////////////////////////////////////
    
#if defined(DATA_EEPROM_BASE)
  // For STM32 devices having integrated EEPROM.
  #include <EEPROM.h>

  #if (DEBUG_WIFIMGR)  
    #warning STM32 devices have integrated EEPROM. Not using buffered API
  #endif
#else  
  /**
   Most STM32 devices don't have an integrated EEPROM. To emulate a EEPROM, the STM32 Arduino core emulated
   the operation of an EEPROM with the help of the embedded flash.
   Writing to a flash is very expensive operation, since a whole flash page needs to be written, even if you only
   want to access the flash byte-wise.
   The STM32 Arduino core provides a buffered access API to the emulated EEPROM. The library has allocated the
   buffer even if you don't use the buffered API, so it's strongly suggested to use the buffered API anyhow.
   */
  #include <FlashStorage_STM32.h>       // https://github.com/khoih-prog/FlashStorage_STM32

  #if (DEBUG_WIFIMGR)  
    #warning STM32 devices have no integrated EEPROM. Using buffered API with FlashStorage_STM32 library
  #endif
#endif    // #if defined(DATA_EEPROM_BASE)

//////////////////////////////////////////////

void ESP_AT_WiFiManager::resetBoard()
{
  // Initialize the IWDG with 2 seconds timeout.
  // This would cause a CPU reset if the IWDG timer
  // is not reloaded in approximately 2 seconds.
  IWatchdog.begin(2000000);
    
  // Back up    
  void(*resetFunc)() = 0;
  resetFunc();
}

//////////////////////////////////////////////

void ESP_AT_WiFiManager::clearConfigData()
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  saveConfigData();
}

//////////////////////////////////////////////

bool ESP_AT_WiFiManager::getConfigData()
{
  hadConfigData = false;
  
#if defined(DATA_EEPROM_BASE)      
      EEPROM.begin();
#endif

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
    strcpy(ESP_AT_WM_Config.host_name,        DEFAULT_HOST_NAME);
    // Don't need
    ESP_AT_WM_Config.checkSum = 0;


    EEPROM.put(EEPROM_START, ESP_AT_WM_Config);

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

//////////////////////////////////////////////

void ESP_AT_WiFiManager::saveConfigData()
{
  int calChecksum = calcChecksum();
  ESP_AT_WM_Config.checkSum = calChecksum;
  
  DEBUG_WM2(F("SaveEEPROM,CSum="), calChecksum);

  EEPROM.put(EEPROM_START, ESP_AT_WM_Config);
}

//////////////////////////////////////////////
    
#endif      //ESP_AT_WiFiManager_impl_STM32_h


