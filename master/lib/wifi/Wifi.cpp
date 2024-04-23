#include "Wifi.h"

Wifi::Wifi() {}

// Conectar à rede Wi-Fi
void Wifi::begin()
{

    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }

    Serial.println("Conectado ao WiFi");

    return;
}