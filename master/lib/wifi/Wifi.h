#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <HTTPClient.h>



class Wifi
{
public:
    Wifi(const char *ssid, const char *password);
};

#endif
