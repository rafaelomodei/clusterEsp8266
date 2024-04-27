#include "MqttBroker.h"

WiFiClient   espClient;
PubSubClient client(espClient);
ManageSlaves manageSlaves;

MqttBroker::MqttBroker(MQTT_BROKER params) {
  mqttServer   = params.server;
  mqttClientId = params.clientId;
  mqttPort     = &params.port;
  mqttUsername = params.userName;
  mqttPassword = params.password;
  mqttOutTopic = params.outTopic;
  mqttInTopic  = params.inTopic;
}

void MqttBroker::callback(char *topic, byte *payload, unsigned int length) {

  Serial.print("MqttBroker::callback ");

  char slave;

  for (int i = 0; i < length; i++) {
    slave = payload[i];
  }

  if (topic == MQTT_HAS_SLAVE_AVAILABLE_TOPIC)
    manageSlaves.add(&slave);

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

boolean MqttBroker::reconnect() {

  if (!client.connect(mqttClientId)) {
    Serial.printf("Falha ao se conectar [ %s ]\n", mqttClientId);
    return client.connected();
  }

  client.subscribe(MQTT_HAS_SLAVE_AVAILABLE_TOPIC);
  Serial.printf("Conectado com sucesso [ %s ]\n", mqttClientId);

  return client.connected();
}

void MqttBroker::setup() {

  const int port = 1883;

  client.setServer(mqttServer, port);
  client.setCallback(MqttBroker::callback);
}

void MqttBroker::loop() {
  if (!client.connected())
    reconnect();

  client.loop();
}

void MqttBroker::publish(const char *topic, const char *payload) {
  client.publish(topic, payload);
}

void MqttBroker::subscribe(const char *topic) { client.subscribe(topic); }
