#ifndef HEADER_H
#define HEADER_H

#include <WiFi.h>
#include <PubSubClient.h>

#include "Database.h"
#include "Wifi.h"
#include "MqttBroker.h"

// Configiração do MQTT Broker
#define MQTT_SERVER "broker.emqx.io"
#define MQTT_CLIENT_ID "ESP32_BROKER"
#define MQTT_TOPIC "emqx/esp32"
#define MQTT_USERNAME "emqx"
#define MQTT_PASSWORD "public"
#define MQTT_OUT_TOPIC "send"
#define MQTT_IN_TOPIC "recive"
#define MQTT_PORT 1883

// Configuração do wifi
#define WIFI_SSID "KDMinternet- MARIA RISSARTTI"
#define WIFI_PASSWORD "shift+tab"

#endif