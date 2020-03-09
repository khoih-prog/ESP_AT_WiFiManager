/****************************************************************************************************************************
 * ESP_AT_WiFiManager.h
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

#ifndef ESP_AT_WiFiManager_h
#define ESP_AT_WiFiManager_h

#if !defined(DEBUG_WIFIMGR)
#define DEBUG_WIFIMGR			false
#endif

#if !defined(ESP_AT_DEBUG_OUTPUT)
#define ESP_AT_DEBUG_OUTPUT Serial
#endif

#define USE_STATIC_WEBSERVER    true

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ESP8266_AT_USE_SAM_DUE)
  #undef ESP8266_AT_USE_SAM_DUE
  #endif
  #define ESP8266_AT_USE_SAM_DUE      true
  #warning Use SAM_DUE architecture from ESP8266_AT_WiFiManager
#endif

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
   || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
   || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) )    
  #if defined(ESP8266_AT_USE_SAMD)
    #undef ESP8266_AT_USE_SAMD
  #endif
  #define ESP8266_AT_USE_SAMD      true
  #warning Use SAMD architecture from ESP8266_AT_WiFiManager
#endif

#ifdef CORE_TEENSY
  #if defined(ESP8266_AT_USE_TEENSY)
    #undef ESP8266_AT_USE_TEENSY
  #endif
  #define ESP8266_AT_USE_TEENSY      true
  #warning Use TEENSY architecture from ESP8266_AT_WiFiManager
#endif

#if ( defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_DUEMILANOVE) || defined(ARDUINO_AVR_YUN) || \
      defined(ARDUINO_AVR_MINI) || defined(ARDUINO_AVR_ETHERNET) || defined(ARDUINO_AVR_FIO) || defined(ARDUINO_AVR_BT) || \
      defined(ARDUINO_AVR_PRO) || defined(ARDUINO_AVR_NG) || defined(ARDUINO_AVR_GEMMA) || defined(ARDUINO_AVR_MEGA) || \
      defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_ADK) || defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_MICRO) || \
      defined(ARDUINO_AVR_ESPLORA) || defined(ARDUINO_AVR_LILYPAD) || defined(ARDUINO_AVR_LILYPAD_USB) || defined(ARDUINO_AVR_ROBOT_CONTROL) || \
      defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || \
      defined(__AVR_ATmega1284__) || defined(__AVR_ATmega2560__) )
  #error This code is intended to run on the AVR platform! Please check your Tools->Board setting.
#endif

#include <avr/pgmspace.h>

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#include <IPAddress.h>
#include <ESP8266_AT_WebServer.h>

#define WFM_LABEL_BEFORE    1
#define WFM_LABEL_AFTER     2
#define WFM_NO_LABEL        0

//KH
//Mofidy HTTP_HEAD to HTTP_HEAD_START to avoid conflict in Arduino esp8266 core 2.6.0+
const char HTTP_200[]  = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
const char HTTP_HEAD_START[]  = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";

const char HTTP_STYLE[]  = "<style>body,textarea,input,select{background: 0;border-radius: 0;font: 16px sans-serif;margin: 0}textarea,input,select{outline: 0;font-size: 14px;border: 1px solid #ccc;padding: 8px;width: 90%}.btn a{text-decoration: none}.container{margin: auto;width: 90%}@media(min-width:1200px){.container{margin: auto;width: 30%}}@media(min-width:768px) and (max-width:1200px){.container{margin: auto;width: 50%}}.btn,h2{font-size: 2em}h1{font-size: 3em}.btn{background: #0ae;border-radius: 4px;border: 0;color: #fff;cursor: pointer;display: inline-block;margin: 2px 0;padding: 10px 14px 11px;width: 100%}.btn:hover{background: #09d}.btn:active,.btn:focus{background: #08b}label>*{display: inline}form>*{display: block;margin-bottom: 10px}textarea:focus,input:focus,select:focus{border-color: #5ab}.msg{background: #def;border-left: 5px solid #59d;padding: 1.5em}.q{float: right;width: 64px;text-align: right}.l{background: no-repeat left center;background-size: 1em}input[type='checkbox']{float: left;width: 20px}.table td{padding:.5em;text-align:left}.table tbody>:nth-child(2n-1){background:#ddd}</style>";

const char HTTP_SCRIPT[]  = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";

const char HTTP_HEAD_END[]  = "</head><body><div class=\"container\">";
const char HTTP_PORTAL_OPTIONS[]  = "<form action=\"/wifi\" method=\"get\"><button class=\"btn\">Configuration</button></form><br/><form action=\"/i\" method=\"get\"><button class=\"btn\">Info</button></form><br/><form action=\"/close\" method=\"get\"><button class=\"btn\">Exit</button></form><br/>";
const char HTTP_ITEM[]  = "<div><a href=\"#p\" onclick=\"c(this)\">{v}</a>&nbsp;<span class=\"q {i}\">{r}%</span></div>";
const char JSON_ITEM[]  = "{\"SSID\":\"{v}\", \"Encrypt\":{i}, \"Quality\":\"{r}\"}";
const char HTTP_FORM_START[]  = "<form method=\"get\" action=\"wifisave\"><label>SSID</label><input id=\"s\" name=\"s\" length=32 placeholder=\"SSID\"><label>PW</label><input id=\"p\" name=\"p\" length=64 placeholder=\"password\">";
const char HTTP_FORM_LABEL[]  = "<label for=\"{i}\">{p}</label>";
const char HTTP_FORM_PARAM[]  = "<input id=\"{i}\" name=\"{n}\" length={l} placeholder=\"{p}\" value=\"{v}\" {c}>";
const char HTTP_FORM_END[]  = "<button class=\"btn\" type=\"submit\">Save</button></form>";
const char HTTP_SAVED[]  = "<div class=\"msg\"><b>Data Saved</b><br>Try connect ESP to the {x} network.<br>Wait 10s and check <a href=\"/\">if OK.</a> <p/>The {v} AP's channel will be same as {x} network. You may have to reconnect to the {v} network.</div>";
const char HTTP_END[]  = "</div></body></html>";

//KH, added 2019/12/15 from Tzapu Development
// http
const char HTTP_HEAD_CL[]               = "Content-Length";
const char HTTP_HEAD_CT[]               = "text/html";
const char HTTP_HEAD_CT2[]              = "text/plain";
const char HTTP_HEAD_CORS[]             = "Access-Control-Allow-Origin";
const char HTTP_HEAD_CORS_ALLOW_ALL[]   = "*";

const char HTTP_HEAD_CC[]               = "Cache-Control";
const char HTTP_HEAD_NCNSMR[]           = "no-cache, no-store, must-revalidate";
const char HTTP_HEAD_PRAGMA[]           = "Pragma";
const char HTTP_HEAD_NOCACHE[]          = "no-cache";
const char HTTP_HEAD_EXPIRE[]           = "Expires";
const char HTTP_HEAD_M_ONE[]            = "-1";

//KH
#define WIFI_MANAGER_MAX_PARAMS 20

class ESP_AT_WMParameter 
{
public:
  ESP_AT_WMParameter(const char *custom);
  ESP_AT_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length);
  ESP_AT_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom);
  ESP_AT_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom, int labelPlacement);

  ~ESP_AT_WMParameter();

  const char *getID();
  const char *getValue();
  const char *getPlaceholder();
  int         getValueLength();
  int         getLabelPlacement();
  const char *getCustomHTML();
private:
  const char *_id;
  const char *_placeholder;
  char       *_value;
  int         _length;
  int         _labelPlacement;
  const char *_customHTML;

  void init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom, int labelPlacement);

  friend class ESP_AT_WiFiManager;
};

typedef struct _ESP_AT_WM_Configuration
{
  char header         [16];
  char wifi_ssid      [32];
  char wifi_pw        [32];
  char host_name      [24];
  int  checkSum;
} ESP_AT_WM_Configuration;

// Currently CONFIG_DATA_SIZE  = 108
uint16_t CONFIG_DATA_SIZE = sizeof(ESP_AT_WM_Configuration);

#define ESP_AT_BOARD_TYPE   "ESP_AT"
#define ESP_AT_NO_CONFIG    "nothing"

//#define EEPROM_SIZE       E2END
//#define EEPROM_SIZE       512

#ifndef EEPROM_SIZE
#define EEPROM_SIZE     512
#else
#if (EEPROM_SIZE > 4096)
#warning EEPROM_SIZE must be <= 4096. Reset to 4096
#undef EEPROM_SIZE
#define EEPROM_SIZE     4096
#endif
#if (EEPROM_SIZE < CONFIG_DATA_SIZE)
#warning EEPROM_SIZE must be > CONFIG_DATA_SIZE. Reset to 512
#undef EEPROM_SIZE
#define EEPROM_SIZE     512
#endif
#endif

#ifndef EEPROM_START
#define EEPROM_START     0
#else
#if (EEPROM_START + CONFIG_DATA_SIZE > EEPROM_SIZE)
#error EPROM_START + CONFIG_DATA_SIZE > EEPROM_SIZE. Please adjust.
#endif
#endif


  #define DEFAULT_PORTAL_TIMEOUT  	60000L

  class ESP_AT_WiFiManager
  {
  public:

    ESP_AT_WiFiManager(void);

    ~ESP_AT_WiFiManager();

    bool       autoConnect(); //Deprecated. Do not use.
    bool       autoConnect(char const *apName, char const *apPassword = NULL); //Deprecated. Do not use.

    //if you want to start the config portal
    bool       startConfigPortal();
    bool       startConfigPortal(char const *apName, char const *apPassword = NULL);

    // get the AP name of the config portal, so it can be used in the callback
    String        getConfigPortalSSID();
    // get the AP password of the config portal, so it can be used in the callback
    String        getConfigPortalPW();

    void          resetSettings();

    //sets timeout before webserver loop ends and exits even if there has been no setup.
    //usefully for devices that failed to connect at some point and got stuck in a webserver loop
    //in seconds setConfigPortalTimeout is a new name for setTimeout
    void          setConfigPortalTimeout(unsigned long seconds);
    void          setTimeout(unsigned long seconds);

    //sets timeout for which to attempt connecting, usefull if you get a lot of failed connects
    void          setConnectTimeout(unsigned long seconds);

    void          setDebugOutput(bool debug);
    //defaults to not showing anything under 8% signal quality if called
    void          setMinimumSignalQuality(int quality = 8);
    //sets AP custom ip configuration
    void          setAPStaticIPConfig(IPAddress ip);
    //sets STA static ip configuration
    void          setSTAStaticIPConfig(IPAddress ip);

    //called when AP mode and config portal is started
    void          setAPCallback(void(*func)(ESP_AT_WiFiManager*));
    //called when settings have been changed and connection was successful
    void          setSaveConfigCallback(void(*func)(void));

    //adds a custom parameter
    bool 				addParameter(ESP_AT_WMParameter *p);

    //if this is set, it will exit after config, even if connection is unsucessful.
    void          setBreakAfterConfig(bool shouldBreak);
    //TODO
    //if this is set, customise style
    void          setCustomHeadElement(const char* element);
    //if this is true, remove duplicated Access Points - defaut true
    void          setRemoveDuplicateAPs(bool removeDuplicates);
    //Scan for WiFiNetworks in range and sort by signal strength
    //space for indices array allocated on the heap and should be freed when no longer required
    int           scanWifiNetworks(int **indicesptr);

    // return SSID of router in STA mode got from config portal. NULL if no user's input //KH
    String				getSSID(void) { return WiFi_SSID(); }

    // return password of router in STA mode got from config portal. NULL if no user's input //KH
    String				getPW(void) { return WiFi_Pass(); }

    //returns the list of Parameters
    ESP_AT_WMParameter** getParameters();
    
    // returns the Parameters Count
    int           getParametersCount();

    const char*   getStatus(int status);

    String WiFi_SSID(void)
    {
      if (!hadConfigData)
        getConfigData();
        
      if (hadConfigData)
        return (String(ESP_AT_WM_Config.wifi_ssid));      
      else
        return ""; 
    }

    String WiFi_Pass(void)
    {
      if (!hadConfigData)
        getConfigData();
        
      if (hadConfigData)
        return (String(ESP_AT_WM_Config.wifi_pw));      
      else
        return ""; 
    }
   
    String IPAddressToString(const IPAddress& address)
    {
      return (String(address[0]) + "." + address[1] + "." + address[2] + "." + address[3]);
    }
    
    void resetBoard(void)
    {
    }
      
    void setAPChannel(int apChannel)
    {
      _apChannel = apChannel;
    }
    
    void clearConfigData(void);

  private:

  ESP_AT_WM_Configuration ESP_AT_WM_Config;
  bool hadConfigData = false;
      
  #if USE_STATIC_WEBSERVER 
  ESP8266_AT_WebServer server;
  #else
  ESP8266_AT_WebServer *server = NULL;
  #endif

    void          setupConfigPortal();

    const char*   _apName     = "ESP_AT_WM_NET";
    const char*   _apPassword = NULL;
    
    // Default channel 10;
    int           _apChannel  = 10;

    unsigned long _configPortalTimeout = 0;

    unsigned long _connectTimeout = 0;
    unsigned long _configPortalStart = 0;

    int numberOfNetworks;
    int *networkIndices;

    IPAddress     _ap_static_ip;
    IPAddress     _sta_static_ip;

    int           _paramsCount = 0;
    int           _minimumQuality = -1;
    bool       _removeDuplicateAPs = true;
    bool       _shouldBreakAfterConfig = false;

    const char*   _customHeadElement = "";

    int           status;
    
    int           connectWifi(String ssid, String pass);
    uint8_t       waitForConnectResult();

    void          handleRoot();
    void          handleWifi();
    void          handleWifiSave();
    void          handleServerClose();
    void          handleInfo();
    void          handleState();
    void          handleScan();
    void          handleReset();
    void          handleNotFound();
    void          reportStatus(String &page);

    //helpers
    int           getRSSIasQuality(int RSSI);
    bool       isIp(String str);
    String        toStringIp(IPAddress ip);

    bool       connect;
    bool       stopConfigPortal = false;
    bool       _debug = false;     //true;

    void(*_apcallback)(ESP_AT_WiFiManager*) = NULL;
    void(*_savecallback)(void) = NULL;

    int                    _max_params;
    ESP_AT_WMParameter** _params;

    template <typename Generic>
    void          DEBUG_WM(Generic text);

    template <class T>
    auto optionalIPFromString(T *obj, const char *s) -> decltype(obj->fromString(s)) {
      return  obj->fromString(s);
    }
    auto optionalIPFromString(...) -> bool {
      DEBUG_WM("NO fromString METHOD ON IPAddress, you need ESP8266 core 2.1.0 or newer for Custom IP configuration to work.");
      return false;
    }
      
    void  displayConfigData(void);
    int   calcChecksum(void);
    bool  getConfigData(void);
    void  saveConfigData(void);    
  };
  
#if DEBUG_WIFIMGR
#define DEBUG_WM1(p1)                 { ESP_AT_DEBUG_OUTPUT.print(F("*WM: ")); ESP_AT_DEBUG_OUTPUT.println(p1); }
#define DEBUG_WM2(p1,p2)              { ESP_AT_DEBUG_OUTPUT.print(F("*WM: ")); ESP_AT_DEBUG_OUTPUT.print(p1); \
                                        ESP_AT_DEBUG_OUTPUT.println(p2); }
#define DEBUG_WM3(p1,p2,p3)           { ESP_AT_DEBUG_OUTPUT.print(F("*WM: ")); ESP_AT_DEBUG_OUTPUT.print(p1); \
                                        ESP_AT_DEBUG_OUTPUT.print(p2); ESP_AT_DEBUG_OUTPUT.println(p3); }
#define DEBUG_WM4(p1,p2,p3,p4)        { ESP_AT_DEBUG_OUTPUT.print(F("*WM: ")); ESP_AT_DEBUG_OUTPUT.print(p1); \
                                        ESP_AT_DEBUG_OUTPUT.print(p2); ESP_AT_DEBUG_OUTPUT.print(p3); ESP_AT_DEBUG_OUTPUT.println(p4); }
#define DEBUG_WM6(p1,p2,p3,p4,p5,p6)  { ESP_AT_DEBUG_OUTPUT.print(F("*WM: ")); ESP_AT_DEBUG_OUTPUT.print(p1); \
                                        ESP_AT_DEBUG_OUTPUT.print(p2); ESP_AT_DEBUG_OUTPUT.print(p3); ESP_AT_DEBUG_OUTPUT.print(p4); \
                                        ESP_AT_DEBUG_OUTPUT.print(p5); ESP_AT_DEBUG_OUTPUT.println(p6); }
#else
#define DEBUG_WM1(p1)
#define DEBUG_WM2(p1,p2)
#define DEBUG_WM3(p1,p2,p3)
#define DEBUG_WM4(p1,p2,p3,p4)
#define DEBUG_WM6(p1,p2,p3,p4,p5,p6)
#endif
                                      
#include "ESP_AT_WiFiManager-impl.h"
 
#if (ESP8266_AT_USE_SAM_DUE)
  //Use DueFlashStorage to simulate EEPROM
  //https://github.com/sebnil/DueFlashStorage
  #include <DueFlashStorage.h>
  DueFlashStorage dueFlashStorage;
  #include "ESP_AT_WiFiManager-impl_DUE.h"
#elif (ESP8266_AT_USE_SAMD)
  //https://github.com/cmaglie/FlashStorage
  #include <FlashStorage.h>
  FlashStorage(ESP_AT_WM_Config_data, ESP_AT_WM_Configuration);
  #include "ESP_AT_WiFiManager-impl_SAMD.h" 
#else     //if defined(CORE_TEENSY)
  #include <EEPROM.h>
  #include "ESP_AT_WiFiManager-impl_Teensy.h"
#endif

#endif
