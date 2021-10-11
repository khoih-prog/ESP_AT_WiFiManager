/********************************************************************************************************************************
  ESP_AT_WiFiManager-impl_Mbed_RPi_Pico.h
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
  Version: 1.3.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      08/03/2020 Initial coding
  1.0.1   K Hoang      22/06/2020 Add support to nRF52 boards, such as AdaFruit Feather nRF52832, NINA_B302_ublox, etc.
  1.0.2   K Hoang      02/07/2020 Add support to ESP32-AT-command shields.
  1.0.3   K Hoang      28/07/2020 Add support to STM32F/L/H/G/WB/MP1 and Seeeduino SAMD21/SAMD51 boards. Add Packages' Patches.
  1.1.0   K Hoang      27/04/2021 Use new FlashStorage_STM32 library. Add support to new STM32 core v2.0.0 and STM32L5
  1.2.0   K Hoang      12/05/2021 Add support to RASPBERRY_PI_PICO using Arduino-pico core
  1.3.0   K Hoang      28/05/2021 Add support to Nano_RP2040_Connect, RASPBERRY_PI_PICO using RP2040 Arduino mbed core
  1.3.1   K Hoang      10/10/2021  Update `platform.ini` and `library.json`
 *********************************************************************************************************************************/

#ifndef ESP_AT_WiFiManager_impl_Mbed_RPi_Pico_h
#define ESP_AT_WiFiManager_impl_Mbed_RPi_Pico_h

#define DEFAULT_HOST_NAME     "MBED-RP2040"

  //Use LittleFS for MBED RPI Pico
  #include "FlashIAPBlockDevice.h"
  #include "LittleFileSystem.h"
  #include "mbed.h"

  #include <stdio.h>
  #include <errno.h>
  #include <functional>

  #include "BlockDevice.h"

  #if !defined(RP2040_FLASH_SIZE)
    #define RP2040_FLASH_SIZE         (2 * 1024 * 1024)
  #endif

  #if !defined(RP2040_FS_LOCATION_END)
  #define RP2040_FS_LOCATION_END    RP2040_FLASH_SIZE
  #endif

  #if !defined(RP2040_FS_SIZE_KB)
    // Using default 16KB for LittleFS
    #define RP2040_FS_SIZE_KB       (64)
  #endif

  #if !defined(RP2040_FS_START)
    #define RP2040_FS_START           (RP2040_FLASH_SIZE - (RP2040_FS_SIZE_KB * 1024))
  #endif

  #if !defined(FORCE_REFORMAT)
    #define FORCE_REFORMAT            false
  #endif

  FlashIAPBlockDevice bd(XIP_BASE + RP2040_FS_START, (RP2040_FS_SIZE_KB * 1024));

  mbed::LittleFileSystem fs("fs");
  
#warning Using LittleFS in ESP_AT_WiFiManager-impl_Mbed_RPi_Pico.h

// Use LittleFS/InternalFS for nRF52
#define  CONFIG_FILENAME              ("/fs/wm_config.dat")
#define  CONFIG_FILENAME_BACKUP       ("/fs/wm_config.bak")

#if 0
typedef struct
{
  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  uint32_t RESERVED0;
  uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  uint32_t RESERVED1;
  uint32_t SHP[2U];                /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
  uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
} SCB_Type;

void NVIC_SystemReset()
{                  
/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos              16U                                      /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)      /*!< SCB AIRCR: VECTKEY Mask */
    
#define SCB_AIRCR_SYSRESETREQ_Pos           2U                                      /*!< SCB AIRCR: SYSRESETREQ Position */
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)       /*!< SCB AIRCR: SYSRESETREQ Mask */    

#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */

                              
  SCB->AIRCR  = ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk);

  while(true);
}
#endif

void ESP_AT_WiFiManager::resetBoard()
{
  delay(1000);
  // Restart for RPI Pico
  // AIRCR.SYSRESETREQ: Writing 1 to this bit causes the SYSRESETREQ
  NVIC_SystemReset();
}

void ESP_AT_WiFiManager::clearConfigData()
{
  memset(&ESP_AT_WM_Config, 0, sizeof(ESP_AT_WM_Config));
  
  saveConfigData();
}

void ESP_AT_WiFiManager::loadConfigData()
{
  DEBUG_WM1(F("LoadCfgFile "));
  
  // file existed
  FILE *file = fopen(CONFIG_FILENAME, "r"); 
    
  if (!file)
  {
    DEBUG_WM1(F("failed"));

    // Trying open redundant config file
    file = fopen(CONFIG_FILENAME_BACKUP, "r");
    DEBUG_WM1(F("LoadBkUpCfgFile "));

    if (!file)
    {
      DEBUG_WM1(F("failed"));
      return;
    }
  }
  
  fseek(file, 0, SEEK_SET);
  fread((uint8_t *) &ESP_AT_WM_Config, 1, sizeof(ESP_AT_WM_Config), file);
  fclose(file);

  DEBUG_WM1(F("OK"));
}

bool initLittleFS()
{
  DEBUG_WM2("LittleFS size (KB) = ", RP2040_FS_SIZE_KB);

  int err = fs.mount(&bd);

  DEBUG_WM1(err ? "LittleFS Mount Fail" : "LittleFS Mount OK");

  if (err || FORCE_REFORMAT)
  { 
    // Reformat if we can't mount the filesystem
    DEBUG_WM1("Formatting... ");

    err = fs.reformat(&bd);
  }

  bool beginOK = (err == 0);
   
  if (!beginOK)
  {
    DEBUG_WM1("\nLittleFS error");
  }

  return beginOK;
}
    
bool ESP_AT_WiFiManager::getConfigData()
{
  hadConfigData = false;
  
  if (!initLittleFS())
    return false;
  
  // if config file exists, load
  loadConfigData();
  
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
    strcpy(ESP_AT_WM_Config.host_name,        DEFAULT_HOST_NAME);
    // Don't need
    ESP_AT_WM_Config.checkSum = 0;

    saveConfigData();

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
  DEBUG_WM1(F("SaveCfgFile "));

  int calChecksum = calcChecksum();
  ESP_AT_WM_Config.checkSum = calChecksum;
  
  DEBUG_WM2(F("WCSum=0x"), String(calChecksum, HEX));

  FILE *file = fopen(CONFIG_FILENAME, "w");

  if (file)
  {
    fseek(file, 0, SEEK_SET);
    fwrite((uint8_t *) &ESP_AT_WM_Config, 1, sizeof(ESP_AT_WM_Config), file);
    fclose(file);
    
    DEBUG_WM1(F("OK"));
  }
  else
  {
    DEBUG_WM1(F("failed"));
  }

  DEBUG_WM1(F("SaveBkUpCfgFile "));

  // Trying open redundant Auth file
  file = fopen(CONFIG_FILENAME_BACKUP, "w");

  if (file)
  {
    fseek(file, 0, SEEK_SET);
    fwrite((uint8_t *) &ESP_AT_WM_Config, 1, sizeof(ESP_AT_WM_Config), file);
    fclose(file);
    DEBUG_WM1(F("OK"));
  }
  else
  {
    DEBUG_WM1(F("failed"));
  } 
}
    
#endif      //ESP_AT_WiFiManager_impl_Mbed_RPi_Pico_h
