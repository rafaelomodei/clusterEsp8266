#ifndef HEADER_H
#define HEADER_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "SortingAlgorithm.h"
#include "MqttBroker.h"
#include "Wifi.h"

// Configiração do MQTT Broker
#define MQTT_SERVER "broker.emqx.io"
#define MQTT_CLIENT_ID "ESP8266_CLIENT_"
#define MQTT_TOPIC "emqx/esp32"
#define MQTT_USERNAME "ESP8266"
#define MQTT_PASSWORD "public"
#define MQTT_OUT_TOPIC "data"
#define MQTT_IN_TOPIC "data"
#define MQTT_HAS_SLAVE_AVAILABLE_TOPIC "HAS_SLEAVE_AVAILABLE"
#define MQTT_PORT 1883

// Configuração do wifi
#define WIFI_SSID "KDMinternet- MARIA RISSARTTI"
#define WIFI_PASSWORD "shift+tab"

#endif