#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WiFi.h>

const char* SSID_AP = "CONFIGURATION";

const char* PASS_AP = "12345678";

IPAddress ESP_IP(192, 168, 1, 222);
IPAddress MASK(255, 255, 255, 0); 


IPAddress AP_IP(4, 4, 4, 4);
IPAddress AP_GATEWAY(4, 4, 4, 4);
IPAddress AP_MASK(255, 255, 255, 0);

uint8_t CH1pin = D1;
uint8_t CH2pin = D6;
uint8_t CH3pin = D2;
//uint8_t CH4pin = D5;

const char* PARAM_SSID = "ssid";
const char* PARAM_PASS = "password";

#endif