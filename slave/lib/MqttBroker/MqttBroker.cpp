#include "MqttBroker.h"

WiFiClient   espClient;
PubSubClient client(espClient);

MqttBroker::MqttBroker(const char *server, int port, const char *userName, const char *password, const char *clientId, const char *outTopic, const char *inTopic) {

  mqttClientId = clientId;
  mqttServer   = server;
  mqttUsername = userName;
  mqttPassword = password;
  mqttOutTopic = outTopic;
  mqttInTopic  = inTopic;
  mqttPort     = port;
}

void MqttBroker::callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Mesagem recebida no topico: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

boolean MqttBroker::reconnect() {
  String mqttCurrentClientId = mqttClientId;
  mqttCurrentClientId += String(WiFi.macAddress());

  if (!client.connect(mqttCurrentClientId.c_str())) {
    Serial.printf("Falha ao se conectar [ %s ]\n", mqttCurrentClientId.c_str());
    return client.connected();
  }

  Serial.printf("Conectado com sucesso [ %s ]\n", mqttCurrentClientId.c_str());
  Serial.printf("Se inscrevendo no topico [ %s ]\n", mqttCurrentClientId.c_str());
  client.subscribe(mqttCurrentClientId.c_str());

  Serial.printf("Publicando no topico [ %s ]\n", MQTT_HAS_SLAVE_AVAILABLE_TOPIC);
  client.publish(MQTT_HAS_SLAVE_AVAILABLE_TOPIC, mqttCurrentClientId.c_str());

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

void MqttBroker::subscribe(const char *topic) {
  client.subscribe(topic);
}
