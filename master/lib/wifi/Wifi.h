#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <HTTPClient.h>

#define SSID "KDMinternet- MARIA RISSARTTI"
#define PASSWORD "shift+tab"

class Wifi
{
public:
    Wifi();
    void begin();
};

#endif
