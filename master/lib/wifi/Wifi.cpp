#include "Wifi.h"

Wifi::Wifi(const char *ssid, const char *password) {

  delay(10);
  Serial.println();
  Serial.print("[ INFO ] - Conectando-se a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("[ INFO ] - WiFi conectado");
  Serial.println("[ INFO ] - Endereço IP: ");
  Serial.println(WiFi.localIP());
}
