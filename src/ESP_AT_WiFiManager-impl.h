/****************************************************************************************************************************
 * ESP_AT_WiFiManager-impl.h
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

#ifndef ESP_AT_WiFiManager_impl_h
#define ESP_AT_WiFiManager_impl_h


ESP_AT_WMParameter::ESP_AT_WMParameter(const char *custom)
{
  _id = NULL;
  _placeholder = NULL;
  _length = 0;
  _value = NULL;
  _labelPlacement = WFM_LABEL_BEFORE;

  _customHTML = custom;
}

ESP_AT_WMParameter::ESP_AT_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length)
{
  init(id, placeholder, defaultValue, length, "", WFM_LABEL_BEFORE);
}

ESP_AT_WMParameter::ESP_AT_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom)
{
  init(id, placeholder, defaultValue, length, custom, WFM_LABEL_BEFORE);
}

ESP_AT_WMParameter::ESP_AT_WMParameter(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom, int labelPlacement)
{
  init(id, placeholder, defaultValue, length, custom, labelPlacement);
}

void ESP_AT_WMParameter::init(const char *id, const char *placeholder, const char *defaultValue, int length, const char *custom, int labelPlacement)
{
  _id = id;
  _placeholder = placeholder;
  _length = length;
  _labelPlacement = labelPlacement;

  _value = new char[_length + 1];

  if (_value != NULL)
  {
    memset(_value, 0, _length + 1);

    if (defaultValue != NULL)
    {
      strncpy(_value, defaultValue, _length);
    }
  }
  _customHTML = custom;
}

ESP_AT_WMParameter::~ESP_AT_WMParameter()
{
  if (_value != NULL)
  {
    delete[] _value;
  }
}

const char* ESP_AT_WMParameter::getValue()
{
  return _value;
}

const char* ESP_AT_WMParameter::getID()
{
  return _id;
}
const char* ESP_AT_WMParameter::getPlaceholder()
{
  return _placeholder;
}

int ESP_AT_WMParameter::getValueLength()
{
  return _length;
}

int ESP_AT_WMParameter::getLabelPlacement()
{
  return _labelPlacement;
}
const char* ESP_AT_WMParameter::getCustomHTML()
{
  return _customHTML;
}


/**
 * [getParameters description]
 * @access public
 */
ESP_AT_WMParameter** ESP_AT_WiFiManager::getParameters() {
  return _params;
}


/**
 * [getParametersCount description]
 * @access public
 */
int ESP_AT_WiFiManager::getParametersCount() {
  return _paramsCount;
}


ESP_AT_WiFiManager::ESP_AT_WiFiManager(void)
{
  _max_params = WIFI_MANAGER_MAX_PARAMS;
  _params = (ESP_AT_WMParameter**)malloc(_max_params * sizeof(ESP_AT_WMParameter*));

  networkIndices = NULL;
}

ESP_AT_WiFiManager::~ESP_AT_WiFiManager()
{
  if (_params != NULL)
  {
    free(_params);
  }

  if (networkIndices)
  {
    free(networkIndices); //indices array no longer required so free memory
  }
}

bool ESP_AT_WiFiManager::addParameter(ESP_AT_WMParameter *p)
{
  if (_paramsCount == _max_params)
  {
    // rezise the params array
    _max_params += WIFI_MANAGER_MAX_PARAMS;
    DEBUG_WM2(F("Increasing _max_params to:"), _max_params);
    ESP_AT_WMParameter** new_params = (ESP_AT_WMParameter**)realloc(_params, _max_params * sizeof(ESP_AT_WMParameter*));

    if (new_params != NULL)
    {
      _params = new_params;
    }
    else
    {
      DEBUG_WM(F("ERROR: Can't realloc params"));
      return false;
    }
  }

  _params[_paramsCount] = p;
  _paramsCount++;
  DEBUG_WM2(F("Adding param "), p->getID());
  return true;
}

void ESP_AT_WiFiManager::setupConfigPortal()
{
  stopConfigPortal = false; //Signal not to close config portal
 
  #if !USE_STATIC_WEBSERVER 
  if (!server)
  {
    server = new ESP8266_AT_WebServer;
  }
  #endif

  _configPortalStart = millis();

  DEBUG_WM2(F("Configure AP: "), _apName);

  if (_apPassword != NULL)
  {
    if (strlen(_apPassword) < 8 || strlen(_apPassword) > 63)
    {
      // fail passphrase to short or long!
      DEBUG_WM(F("Bad AP password. Ignoring"));
      _apPassword = NULL;
    }
    else
    {
      DEBUG_WM2(F("AP PW: "),_apPassword);
    }
  }

  //optional soft ip config
  if (_ap_static_ip)
  {
    DEBUG_WM2(F("Custom AP IP: "), _ap_static_ip);
    WiFi.configAP(_ap_static_ip);
  }
 
  if (_apPassword != NULL)
  {   
    // Use AP_STA to scan WiFi
    WiFi.beginAP(_apName, _apChannel, _apPassword, ENC_TYPE_WPA2_PSK, false);
  }
  else
  {
    WiFi.beginAP(_apName, _apChannel, NULL, ENC_TYPE_WPA2_PSK, false);
  }

  delay(500); // Without delay I've seen the IP address blank
  DEBUG_WM2(F("AP IP: "), WiFi.localIP());

  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
  #if USE_STATIC_WEBSERVER 
  
    server.on("/", [this](){ handleRoot(); });
    server.on("/wifi", [this](){ handleWifi(); });
    server.on("/wifisave", [this](){ handleWifiSave(); });
    server.on("/close", [this](){ handleServerClose(); });
    server.on("/i", [this](){ handleInfo(); });
    server.onNotFound( [this](){ handleNotFound(); });
    
    server.begin(); // Web server start
  
  #else
   
    server->on("/", [this](){ handleRoot(); });
    server->on("/wifi", [this](){ handleWifi(); });
    server->on("/wifisave", [this](){ handleWifiSave(); });
    server->on("/close", [this](){ handleServerClose(); });
    server->on("/i", [this](){ handleInfo(); });
    server->onNotFound( [this](){ handleNotFound(); });
    
    server->begin(); // Web server start
  #endif
  
  DEBUG_WM2(F("HTTP server on channel "), _apChannel);

}

bool ESP_AT_WiFiManager::autoConnect()
{
  String ssid = "ESP_AT_ABCDEF";

  return autoConnect(ssid.c_str(), NULL);
}

/* This is not very useful as there has been an assumption that device has to be
told to connect but Wifi already does it's best to connect in background. Calling this
method will block until WiFi connects. Sketch can avoid
blocking call then use (WiFi.status()==WL_CONNECTED) test to see if connected yet.
See some discussion at https://github.com/tzapu/WiFiManager/issues/68
*/
bool ESP_AT_WiFiManager::autoConnect(char const *apName, char const *apPassword)
{
  DEBUG_WM(F("AutoConnect"));

  // device will attempt to connect by itself; wait 10 secs
  // to see if it succeeds and should it fail, fall back to AP
  unsigned long startedAt = millis();

  while (millis() - startedAt < 10000)
  {
    delay(200);

    if (WiFi.status() == WL_CONNECTED)
    {
      DEBUG_WM4(F("After "), (float) (millis() - startedAt) / 1000, F(" secs, local ip: "), WiFi.localIP() );
      return true;
    }
  }

  return startConfigPortal(apName, apPassword);
}

bool  ESP_AT_WiFiManager::startConfigPortal()
{
  String ssid = "ESP_AT_ABCDEF";

  ssid.toUpperCase();
  
  return startConfigPortal(ssid.c_str(), NULL);
}

bool  ESP_AT_WiFiManager::startConfigPortal(char const *apName, char const *apPassword)
{
  _apName = apName;
  _apPassword = apPassword;

  //notify we entered AP mode
  if (_apcallback != NULL)
  {
    DEBUG_WM(F("_apcallback"));
    _apcallback(this);
  }

  connect = false;
  
  setupConfigPortal();

  bool TimedOut = true;
  
  while (_configPortalTimeout == 0 || millis() < _configPortalStart + _configPortalTimeout)
  {   
    #if USE_STATIC_WEBSERVER
    server.handleClient();
    #else
    server->handleClient();
    #endif
    
    if (connect)
    {
      TimedOut = false;
      delay(2000);

      DEBUG_WM(F("Connect to new AP"));

      // using user-provided  _ssid, _pass in place of system-stored ssid and pass
      if (connectWifi(WiFi_SSID(), WiFi_Pass()) != WL_CONNECTED)
      {
        DEBUG_WM(F("Failed to connect."));
      }
      else
      {
        //notify that configuration has changed and any optional parameters should be saved
        if (_savecallback != NULL)
        {
          //todo: check if any custom parameters actually exist, and check if they really changed maybe
          _savecallback();
        }
        break;
      }

      if (_shouldBreakAfterConfig)
      {
        //flag set to exit after config after trying to connect
        //notify that configuration has changed and any optional parameters should be saved
        if (_savecallback != NULL)
        {
          //todo: check if any custom parameters actually exist, and check if they really changed maybe
          _savecallback();
        }
        break;
      }
    }

    if (stopConfigPortal)
    {
      DEBUG_WM(F("Stop ConfigPortal"));  	//KH
      stopConfigPortal = false;
      break;
    }
    yield();
  }

  if (TimedOut)
  {
    WiFi.reset();
    
    // check if we've got static_ip settings, if we do, use those.
    if (_sta_static_ip)
    {
      WiFi.config(_sta_static_ip);
      DEBUG_WM2(F("Static IP : "), _sta_static_ip);
    }
    
    WiFi.begin(WiFi_SSID().c_str(), WiFi_Pass().c_str());
    
    DEBUG_WM2(F("Timeout, connect result: "), getStatus(waitForConnectResult()));
  }
 
  #if USE_STATIC_WEBSERVER 
    server.stop();
  #else
    server->stop();
  #endif
  
  return  WiFi.status() == WL_CONNECTED;
}

int ESP_AT_WiFiManager::connectWifi(String ssid, String pass)
{
  DEBUG_WM(F("Connect wifi with new params"));

  if (ssid != "")
  {
    resetSettings();

    //fix for auto connect racing issue
    if (WiFi.status() == WL_CONNECTED)
    {
      DEBUG_WM(F("Connected. Exit."));
      return WL_CONNECTED;
    }

    //TO DO, STA mode only
    WiFi.reset();
    
    // check if we've got static_ip settings, if we do, use those.
    if (_sta_static_ip)
    {
      WiFi.config(_sta_static_ip);
      DEBUG_WM2(F("Static IP : "), _sta_static_ip);
    }
    
    WiFi.begin(ssid.c_str(), pass.c_str());   // Start Wifi with new values.
  }
  else if (WiFi_SSID() == "")
  {
    DEBUG_WM(F("No saved data"));
  }

  int connRes = waitForConnectResult();
  DEBUG_WM2(F("Connect result: "), getStatus(connRes));

  return connRes;
}

uint8_t ESP_AT_WiFiManager::waitForConnectResult()
{
  if (_connectTimeout == 0)
  {
    return WiFi.status();
  }
  else
  {
    DEBUG_WM(F("Connect with timeout"));
    unsigned long start = millis();
    bool keepConnecting = true;
    uint8_t status;

    while (keepConnecting)
    {
      status = WiFi.status();
      if (millis() > start + _connectTimeout)
      {
        keepConnecting = false;
        DEBUG_WM(F("Connect timeout"));
      }

      if (status == WL_CONNECTED || status == WL_CONNECT_FAILED)
      {
        keepConnecting = false;
      }
      delay(100);
    }
    return status;
  }
}

//Convenient for debugging but wasteful of program space.
//Remove if short of space
const char* ESP_AT_WiFiManager::getStatus(int status)
{
  switch (status)
  {
  case WL_IDLE_STATUS:
    return "WL_IDLE_STATUS";
  case WL_CONNECTED:
    return "WL_CONNECTED";
  case WL_CONNECT_FAILED:
    return "WL_CONNECT_FAILED";
  case WL_DISCONNECTED:
    return "WL_DISCONNECTED";
  default:
    return "UNKNOWN";
  }
}

String ESP_AT_WiFiManager::getConfigPortalSSID()
{
  return _apName;
}

String ESP_AT_WiFiManager::getConfigPortalPW()
{
  return _apPassword;
}

void ESP_AT_WiFiManager::resetSettings()
{
  DEBUG_WM(F("Data cleared"));
  
  WiFi.disconnect();
  
  delay(200);
  return;
}

void ESP_AT_WiFiManager::setTimeout(unsigned long seconds)
{
  setConfigPortalTimeout(seconds);
}

void ESP_AT_WiFiManager::setConfigPortalTimeout(unsigned long seconds)
{
  _configPortalTimeout = seconds * 1000;
}

void ESP_AT_WiFiManager::setConnectTimeout(unsigned long seconds)
{
  _connectTimeout = seconds * 1000;
}

void ESP_AT_WiFiManager::setDebugOutput(bool debug)
{
  _debug = debug;
}

void ESP_AT_WiFiManager::setAPStaticIPConfig(IPAddress ip)
{
  _ap_static_ip = ip;
}

void ESP_AT_WiFiManager::setSTAStaticIPConfig(IPAddress ip)
{
  _sta_static_ip = ip;
}

void ESP_AT_WiFiManager::setMinimumSignalQuality(int quality)
{
  _minimumQuality = quality;
}

void ESP_AT_WiFiManager::setBreakAfterConfig(bool shouldBreak)
{
  _shouldBreakAfterConfig = shouldBreak;
}

void ESP_AT_WiFiManager::reportStatus(String &page)
{
  if (WiFi_SSID() != "")
  {
    page += F("Config for <b>");
    page += WiFi_SSID();

    if (WiFi.status() == WL_CONNECTED)
    {
      page += F(" and connected</b> on IP <a href=\"http://");
      page += IPAddressToString(WiFi.localIP());
      page += F("/\">");
      page += IPAddressToString(WiFi.localIP());
      page += F("</a>");
    }
    else
    {
      page += F(" but not connected</b>");
    }
  }
  else
  {
    page += F("No AP configured.");
  }
}

/** Handle root or redirect to captive portal */
void ESP_AT_WiFiManager::handleRoot()
{
  DEBUG_WM(F("Handle root"));

  // Disable _configPortalTimeout when someone accessing Portal to give some time to config
  _configPortalTimeout = 0;		//KH 

  #if USE_STATIC_WEBSERVER 
    server.sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server.sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server.sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #else 
    server->sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server->sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server->sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #endif
  
  String page = (HTTP_HEAD_START);
  page.replace("{v}", "Options");
  page += (HTTP_SCRIPT);
  page += (HTTP_STYLE);
  page += _customHeadElement;
  page += (HTTP_HEAD_END);
  page += F("<h2>");
  page += _apName;

  if (WiFi_SSID() != "")
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      page += F(" on ");
      page += WiFi_SSID();
    }
    else
    {
      page += F(" <s>on ");
      page += WiFi_SSID();
      page += F("</s>");
    }
  }

  page += F("</h2>");
  page += (HTTP_PORTAL_OPTIONS);
  page += F("<div class=\"msg\">");
  
  reportStatus(page);

  page += F("</div>");
  page += (HTTP_END);
  
  #if USE_STATIC_WEBSERVER 
    server.send(200, HTTP_HEAD_CT, page);
  #else
   server->send(200, HTTP_HEAD_CT, page);
  #endif

}

/** Wifi config page handler */
void ESP_AT_WiFiManager::handleWifi()
{
  DEBUG_WM(F("Handle WiFi"));

  // Disable _configPortalTimeout when someone accessing Portal to give some time to config
  _configPortalTimeout = 0;		//KH 

  #if USE_STATIC_WEBSERVER 
    server.sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server.sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server.sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #else 
    server->sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server->sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server->sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #endif
  
  
  String page = (HTTP_HEAD_START);
  page.replace("{v}", "Config ESP");
  page += (HTTP_SCRIPT);
  page += (HTTP_STYLE);
  page += _customHeadElement;
  page += (HTTP_HEAD_END);
  page += F("<h2>Configuration</h2>");

  numberOfNetworks = scanWifiNetworks(&networkIndices);

  //Print list of WiFi networks that were found in earlier scan
  if (numberOfNetworks == 0)
  {
    page += F("No network found. Restart to scan again.");
  }
  else
  {
    //display networks in page
    //Limit numberOfNetworks to 3 to reduce size
    numberOfNetworks = 3;
    
    for (int i = 0; i < numberOfNetworks; i++)
    {
      if (networkIndices[i] == -1)
        continue; // skip dups and those that are below the required quality

      DEBUG_WM3(WiFi.SSID(networkIndices[i]), F(" / "), WiFi.RSSI(networkIndices[i]));

      int quality = getRSSIasQuality(WiFi.RSSI(networkIndices[i]));

      String item = (HTTP_ITEM);
      String rssiQ;
      rssiQ += quality;
      item.replace("{v}", WiFi.SSID(networkIndices[i]));
      item.replace("{r}", rssiQ);

      if (WiFi.encryptionType(networkIndices[i]) != ENC_TYPE_NONE)
      {
        item.replace("{i}", "l");
      }
      else
      {
        item.replace("{i}", "");
      }

      page += item;
      delay(0);
    }

    page += "<br/>";
  }

  page += (HTTP_FORM_START);
  char parLength[2];

  // add the extra parameters to the form
  for (int i = 0; i < _paramsCount; i++)
  {
    if (_params[i] == NULL)
    {
      break;
    }

    String pitem;
    switch (_params[i]->getLabelPlacement())
    {
    case WFM_LABEL_BEFORE:
      pitem = (HTTP_FORM_LABEL);
      pitem += (HTTP_FORM_PARAM);
      break;
    case WFM_LABEL_AFTER:
      pitem = (HTTP_FORM_PARAM);
      pitem += (HTTP_FORM_LABEL);
      break;
    default:
      // WFM_NO_LABEL
      pitem = (HTTP_FORM_PARAM);
      break;
    }

    if (_params[i]->getID() != NULL)
    {
      pitem.replace("{i}", _params[i]->getID());
      pitem.replace("{n}", _params[i]->getID());
      pitem.replace("{p}", _params[i]->getPlaceholder());
      snprintf(parLength, 2, "%d", _params[i]->getValueLength());
      pitem.replace("{l}", parLength);
      pitem.replace("{v}", _params[i]->getValue());
      pitem.replace("{c}", _params[i]->getCustomHTML());
    }
    else
    {
      pitem = _params[i]->getCustomHTML();
    }

    page += pitem;
  }

  if (_params[0] != NULL)
  {
    page += F("<br/>");
  }

  page += (HTTP_FORM_END);

  page += (HTTP_END);

  #if USE_STATIC_WEBSERVER 
  server.send(200, HTTP_HEAD_CT, page);
  #else
  server->send(200, HTTP_HEAD_CT, page);
  #endif

  DEBUG_WM(F("Sent config page"));
}

/** Handle the WLAN save form and redirect to WLAN config page again */
void ESP_AT_WiFiManager::handleWifiSave()
{
  DEBUG_WM(F("WiFi save"));

  //SAVE/connect here
  
  #if USE_STATIC_WEBSERVER 
  if (strlen(server.arg("s").c_str()) < sizeof(ESP_AT_WM_Config.wifi_ssid) - 1)
    strcpy(ESP_AT_WM_Config.wifi_ssid, server.arg("s").c_str());
  else
    strncpy(ESP_AT_WM_Config.wifi_ssid, server.arg("s").c_str(), sizeof(ESP_AT_WM_Config.wifi_ssid) - 1);
    
  if (strlen(server.arg("p").c_str()) < sizeof(ESP_AT_WM_Config.wifi_pw) - 1)
    strcpy(ESP_AT_WM_Config.wifi_pw, server.arg("p").c_str());
  else
    strncpy(ESP_AT_WM_Config.wifi_pw, server.arg("p").c_str(), sizeof(ESP_AT_WM_Config.wifi_pw) - 1);
  #else
  
  if (strlen(server->arg("s").c_str()) < sizeof(ESP_AT_WM_Config.wifi_ssid) - 1)
    strcpy(ESP_AT_WM_Config.wifi_ssid, server->arg("s").c_str());
  else
    strncpy(ESP_AT_WM_Config.wifi_ssid, server->arg("s").c_str(), sizeof(ESP_AT_WM_Config.wifi_ssid) - 1);
    
  if (strlen(server->arg("p").c_str()) < sizeof(ESP_AT_WM_Config.wifi_pw) - 1)
    strcpy(ESP_AT_WM_Config.wifi_pw, server->arg("p").c_str());
  else
    strncpy(ESP_AT_WM_Config.wifi_pw, server->arg("p").c_str(), sizeof(ESP_AT_WM_Config.wifi_pw) - 1);
  #endif 
  
  //parameters
  for (int i = 0; i < _paramsCount; i++)
  {
    if (_params[i] == NULL)
    {
      break;
    }

    //read parameter
    #if USE_STATIC_WEBSERVER
    String value = server.arg(_params[i]->getID()).c_str();
    #else
    String value = server->arg(_params[i]->getID()).c_str();
    #endif
    
    //store it in array
    value.toCharArray(_params[i]->_value, _params[i]->_length);
    DEBUG_WM4(F("Param:"), _params[i]->getID(), F(" / Value:"), value);
  }

  #if USE_STATIC_WEBSERVER
  if (server.arg("ip") != "")
  #else
  if (server->arg("ip") != "")
  #endif
  {
    DEBUG_WM(F("static ip"));
    
    #if USE_STATIC_WEBSERVER
      DEBUG_WM(server.arg("ip"));
      String ip = server.arg("ip");
    #else
      DEBUG_WM(server->arg("ip"));
      String ip = server->arg("ip");
    #endif
    
    optionalIPFromString(&_sta_static_ip, ip.c_str());
  }

  String page = (HTTP_HEAD_START);
  page.replace("{v}", "Data Saved");
  page += (HTTP_SCRIPT);
  page += (HTTP_STYLE);
  page += _customHeadElement;
  page += (HTTP_HEAD_END);
  page += (HTTP_SAVED);
  page.replace("{v}", _apName);
  page.replace("{x}", ESP_AT_WM_Config.wifi_ssid);
  page += (HTTP_END);
  
  // Save to EEPROM
  saveConfigData();

  #if USE_STATIC_WEBSERVER
    server.send(200, HTTP_HEAD_CT, page);
  #else
    server->send(200, HTTP_HEAD_CT, page);
  #endif

  DEBUG_WM(F("Sent wifisave page"));

  connect = true; //signal ready to connect/reset

    // Restore when Press Save WiFi
  _configPortalTimeout = DEFAULT_PORTAL_TIMEOUT;
}

/** Handle shut down the server page */
void ESP_AT_WiFiManager::handleServerClose()
{
  DEBUG_WM1(F("Server Close"));
  
  #if USE_STATIC_WEBSERVER 
    server.sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server.sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server.sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #else 
    server->sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server->sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server->sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #endif
  
  String page = (HTTP_HEAD_START);
  page.replace("{v}", "Close Server");
  page += (HTTP_SCRIPT);
  page += (HTTP_STYLE);
  page += _customHeadElement;
  page += (HTTP_HEAD_END);
  page += F("<div class=\"msg\">");
  page += F("SSID <b>");
  page += WiFi_SSID();
  page += F("</b><br>");
  
  page += F("IP: <b>");
  if (_sta_static_ip)
  {
    page += IPAddressToString(_sta_static_ip);
  }
  else
  {
    page += F("DHCP");
  }
  
  page += F("</b><br><br>");
  page += F("Config Portal closed.<br><br>");
  page += (HTTP_END);
  
  #if USE_STATIC_WEBSERVER
  server.send(200, HTTP_HEAD_CT, page);
  #else
  server->send(200, HTTP_HEAD_CT, page);
  #endif
  
  //stopConfigPortal = true; //signal ready to shutdown config portal		//KH crash if use this ???
  DEBUG_WM1(F("Sent server close page"));

  // Restore when Press Save WiFi
  _configPortalTimeout = DEFAULT_PORTAL_TIMEOUT;
}

/** Handle the info page */
void ESP_AT_WiFiManager::handleInfo()
{
  DEBUG_WM(F("Info"));

  // Disable _configPortalTimeout when someone accessing Portal to give some time to config
  _configPortalTimeout = 0;		//KH 

  #if USE_STATIC_WEBSERVER 
    server.sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server.sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server.sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #else 
    server->sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server->sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server->sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
  #endif
  
  String page = (HTTP_HEAD_START);
  page.replace("{v}", "Info");
  page += (HTTP_SCRIPT);
  page += (HTTP_STYLE);
  page += _customHeadElement;
  page += (HTTP_HEAD_END);
  page += F("<h2>WiFi Info</h2>");
  reportStatus(page);
  page += F("<h3>Device Data</h3>");
  page += F("<table class=\"table\">");
  page += F("<thead><tr><th>Name</th><th>Value</th></tr></thead><tbody><tr><td>Mac</td><td>");

  // Only for ESP8266 AT
  char _macAddress[WL_MAC_ADDR_LENGTH + 1];
  WiFi.macAddress((uint8_t *) _macAddress);
  _macAddress[WL_MAC_ADDR_LENGTH] = 0;
     
  String _macAdd = String(_macAddress[0], HEX) + ":" + String(_macAddress[1], HEX) + ":" 
                 + String(_macAddress[2], HEX) + ":" + String(_macAddress[3], HEX) + ":" 
                 + String(_macAddress[3], HEX) + ":" + String(_macAddress[5], HEX);
                                  
  _macAdd.toUpperCase();
  
  page += String( _macAdd );
  
  page += F("<tr><td>AP IP</td><td>");
  page += IPAddressToString(WiFi.localIP());
  page += F("</td></tr>");

  page += F("<tr><td>SSID</td><td>");
  page += WiFi_SSID();
  page += F("</td></tr>");

  page += F("<tr><td>STA IP</td><td>");
  page += IPAddressToString(WiFi.localIP());
  page += F("</td></tr>");

  page += F("</td></tr>");
  page += F("</tbody></table>");

  page += F("<p/>More info about ESP_AT_WiFiManager at");
  page += F("<p/><a href=\"https://github.com/khoih-prog/ESP_AT_WiFiManager\">ESP_AT_WiFiManager</a>");
  page += (HTTP_END);

  #if USE_STATIC_WEBSERVER
    server.send(200, HTTP_HEAD_CT, page);
  #else
    server->send(200, HTTP_HEAD_CT, page);
  #endif

  DEBUG_WM(F("Sent info page"));
}

void ESP_AT_WiFiManager::handleNotFound()
{
  String message = "File Not Found\n\n";
  
  #if USE_STATIC_WEBSERVER
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++)
    {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
   
    server.sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server.sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server.sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
    server.send(404, HTTP_HEAD_CT2, message);
  #else
    message += "URI: ";
    message += server->uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server->args();
    message += "\n";

    for (uint8_t i = 0; i < server->args(); i++)
    {
      message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
    }

    server->sendHeader(HTTP_HEAD_CC, HTTP_HEAD_NCNSMR);
    server->sendHeader(HTTP_HEAD_PRAGMA, HTTP_HEAD_NOCACHE);
    server->sendHeader(HTTP_HEAD_EXPIRE, HTTP_HEAD_M_ONE);
    server->send(404, HTTP_HEAD_CT2, message);
  #endif
}

//start up config portal callback
void ESP_AT_WiFiManager::setAPCallback(void(*func)(ESP_AT_WiFiManager* myWiFiManager))
{
  _apcallback = func;
}

//start up save config callback
void ESP_AT_WiFiManager::setSaveConfigCallback(void(*func)(void))
{
  _savecallback = func;
}

//sets a custom element to add to head, like a new style tag
void ESP_AT_WiFiManager::setCustomHeadElement(const char* element) {
  _customHeadElement = element;
}

//if this is true, remove duplicated Access Points - defaut true
void ESP_AT_WiFiManager::setRemoveDuplicateAPs(bool removeDuplicates)
{
  _removeDuplicateAPs = removeDuplicates;
}

//Scan for WiFiNetworks in range and sort by signal strength
//space for indices array allocated on the heap and should be freed when no longer required
int ESP_AT_WiFiManager::scanWifiNetworks(int **indicesptr)
{
#if DEBUG_WIFIMGR
  DEBUG_WM(F("Scan Network"));
#endif

  int n = WiFi.scanNetworks();

  //KH, Terrible bug here. WiFi.scanNetworks() returns n < 0 => malloc( negative == very big ) => crash!!!
  //In .../esp32/libraries/WiFi/src/WiFiType.h
  //#define WIFI_SCAN_RUNNING   (-1)
  //#define WIFI_SCAN_FAILED    (-2)
  //if (n == 0)
  if (n <= 0)
  {
    DEBUG_WM(F("None found"));
    return(0);
  }
  else
  {
    // Allocate space off the heap for indices array.
    // This space should be freed when no longer required.
    int* indices = (int *)malloc(n * sizeof(int));

    if (indices == NULL)
    {
      DEBUG_WM(F("ERROR: Out of memory"));
      *indicesptr = NULL;
      return(0);
    }

    *indicesptr = indices;


    //sort networks
    for (int i = 0; i < n; i++)
    {
      indices[i] = i;
    }

    // RSSI SORT
    // old sort
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i]))
        {
          swap(indices[i], indices[j]);
        }
      }
    }

    // remove duplicates ( must be RSSI sorted )
    if (_removeDuplicateAPs)
    {
      String cssid;
      for (int i = 0; i < n; i++)
      {
        if (indices[i] == -1)
          continue;

        cssid = WiFi.SSID(indices[i]);
        for (int j = i + 1; j < n; j++)
        {
          if (cssid == WiFi.SSID(indices[j]))
          {
            DEBUG_WM(String("DUP AP: ") + WiFi.SSID(indices[j]));
            indices[j] = -1; // set dup aps to index -1
          }
        }
      }
    }

    for (int i = 0; i < n; i++)
    {
      if (indices[i] == -1)
        continue; // skip dups

      int quality = getRSSIasQuality(WiFi.RSSI(indices[i]));

      if (!(_minimumQuality == -1 || _minimumQuality < quality))
      {
        indices[i] = -1;
        DEBUG_WM(F("Skip: low quality"));
      }
    }

    return (n);
  }
}

template <typename Generic>
void ESP_AT_WiFiManager::DEBUG_WM(Generic text)
{
  if (_debug)
  {
    ESP_AT_DEBUG_OUTPUT.print(F("*WM: "));
    ESP_AT_DEBUG_OUTPUT.println(text);
  }
}

int ESP_AT_WiFiManager::getRSSIasQuality(int RSSI)
{
  int quality = 0;

  if (RSSI <= -100)
  {
    quality = 0;
  }
  else if (RSSI >= -50)
  {
    quality = 100;
  }
  else
  {
    quality = 2 * (RSSI + 100);
  }

  return quality;
}

/** Is this an IP? */
bool ESP_AT_WiFiManager::isIp(String str)
{
  for (uint16_t i = 0; i < str.length(); i++)
  {
    int c = str.charAt(i);

    if (c != '.' && (c < '0' || c > '9'))
    {
      return false;
    }
  }
  return true;
}

/** IP to String? */
String ESP_AT_WiFiManager::toStringIp(IPAddress ip)
{
  String res = "";
  for (int i = 0; i < 3; i++)
  {
    res += String((ip >> (8 * i)) & 0xFF) + ".";
  }

  res += String(((ip >> 8 * 3)) & 0xFF);

  return res;
}

void ESP_AT_WiFiManager::displayConfigData(void)
{
  DEBUG_WM6(F("Header = "), ESP_AT_WM_Config.header, F(", SSID = "), ESP_AT_WM_Config.wifi_ssid,
             F(", PW = "),   ESP_AT_WM_Config.wifi_pw);
  DEBUG_WM2(F("Host Name = "), ESP_AT_WM_Config.host_name);
}

int ESP_AT_WiFiManager::calcChecksum(void)
{
  int checkSum = 0;
  for (uint16_t index = 0; index < (sizeof(ESP_AT_WM_Config) - sizeof(ESP_AT_WM_Config.checkSum)); index++)
  {
    checkSum += * ( ( (byte*) &ESP_AT_WM_Config ) + index);
  }

  return checkSum;
}

#endif    //ESP_AT_WiFiManager-impl_h

