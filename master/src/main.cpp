#include "header.h"

// Instancie a classe MQTTBroker
MqttBroker mqttBroker({
  server : MQTT_SERVER,
  userName : MQTT_USERNAME,
  password : MQTT_PASSWORD,
  clientId : MQTT_CLIENT_ID,
  outTopic : MQTT_OUT_TOPIC,
  inTopic : MQTT_IN_TOPIC,
  port : MQTT_PORT,
});

void setup() {
  Serial.begin(115200);

  Wifi(WIFI_SSID, WIFI_PASSWORD);

  Database db;

  // Configuração inicial do MQTT
  mqttBroker.setup();

  Serial.print("Data base: ");

  serializeJsonPretty(db.getUnorderedList(1), Serial);
}

void loop() {
  mqttBroker.loop();

  // Mantenha a conexão MQTT ativa
}
