#include <Arduino.h>
#include <config.h>
#include <html_content.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <EEPROM.h>

AsyncWebServer server(80);

String ssid;
String password;

//Preferences prefs;

bool btn1State = false;
bool btn2State = false;
bool btn3State = false;

  void saveConfig() {
    EEPROM.begin(512);
    int addr = 0;
    for (uint i = 0; i < ssid.length(); i++) {
      EEPROM.write(addr++, ssid[i]);
    }
    EEPROM.write(addr++, 0);
    for (uint i = 0; i < password.length(); i++) {
      EEPROM.write(addr++, password[i]);
    }
    EEPROM.write(addr, 0);
    EEPROM.commit();
    EEPROM.end();
  }
  
  bool loadConfig() {
    EEPROM.begin(512);
    int addr = 0;
    char c;
    ssid = "";
    password = "";
  
    while ((c = EEPROM.read(addr++)) != 0 && addr < 512) {
      ssid += c;
    }
  
    while ((c = EEPROM.read(addr++)) != 0 && addr < 512) {
      password += c;
    }
    EEPROM.end();
    return (ssid.length() > 0 && password.length() > 0);
  }

// void saveConfig() {
//   prefs.begin("wifi-config", false); 
//   prefs.putString("ssid", ssid);
//   prefs.putString("password", password);
//   prefs.end();
// }

// bool loadConfig() {
//   prefs.begin("wifi-config", true); 
//   ssid = prefs.getString("ssid", "");
//   password = prefs.getString("password", "");
//   prefs.end();
//   return (ssid.length() > 0 && password.length() > 0);
// }

void startConfigServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", configPage);
  });

  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam(PARAM_SSID, true) && request->hasParam(PARAM_PASS, true)) {
      ssid = request->getParam(PARAM_SSID, true)->value();
      password = request->getParam(PARAM_PASS, true)->value();
      saveConfig();
      request->send(200, "text/plain", "Success. Restart...");
      delay(1000);
      ESP.restart();
    } else {
      request->send(400, "text/plain", "Invalid parameters");
    }
  });

  server.begin();
}

void setPinStatus(int pin, bool state) {
  digitalWrite(pin, state ? LOW : HIGH);
}

void startHauptServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", mainPage);
  });

  server.on("/btn1", HTTP_POST, [](AsyncWebServerRequest *request){
    btn1State = !btn1State; 
    setPinStatus(CH1pin, btn1State);
    request->send(200, "text/plain", btn1State ? "1" : "0");
  });

  server.on("/btn2", HTTP_POST, [](AsyncWebServerRequest *request){
    btn2State = !btn2State; 
    setPinStatus(CH2pin, btn2State);
    request->send(200, "text/plain", btn2State ? "1" : "0");
  });

  server.on("/btn3", HTTP_POST, [](AsyncWebServerRequest *request){
    btn3State = !btn3State; 
    setPinStatus(CH3pin, btn3State);
    request->send(200, "text/plain", btn3State ? "1" : "0");
  });
  
  server.begin();
}

void setup() {
  Serial.begin(115200);

  pinMode(CH1pin, OUTPUT); digitalWrite(CH1pin, HIGH);
  pinMode(CH2pin, OUTPUT); digitalWrite(CH2pin, HIGH);
  pinMode(CH3pin, OUTPUT); digitalWrite(CH3pin, HIGH);

  if (loadConfig()) {
    if (!WiFi.config(ESP_IP, IPAddress(0, 0, 0, 0), MASK)) {
      Serial.println("Failed to configure static IP");
    }
    WiFi.begin(ssid.c_str(), password.c_str());
    
    int a = 0;
    while (WiFi.status() != WL_CONNECTED && a < 20) {
      delay(500);
      Serial.print(".");
      a++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to WiFi");
      Serial.println(WiFi.localIP());
      
      startHauptServer();
      return;
    }
  }

  WiFi.mode(WIFI_AP);

  WiFi.softAPConfig(AP_IP, AP_GATEWAY, AP_MASK);
  WiFi.softAP(SSID_AP, PASS_AP);
  Serial.println(WiFi.softAPIP());
  
  startConfigServer();
}

void loop() {
  
}