#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>

class Wifi {
public:
  Wifi(const char *ssid, const char *password);
};

#endif
