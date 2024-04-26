#ifndef WIFI_H
#define WIFI_H

#include <HTTPClient.h>
#include <WiFi.h>

class Wifi {
public:
  Wifi(const char *ssid, const char *password);
};

#endif
