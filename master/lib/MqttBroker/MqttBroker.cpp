#include "MqttBroker.h"

WiFiClient   espClient;
PubSubClient client(espClient);

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

  Serial.print("Mesagem recebida no topico: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  ManageSlaves *manageSlaves = ManageSlaves::getInstance();

  char *slave = (char *)malloc(length + 1);

  // Inicializa a memória alocada com zeros
  memset(slave, 0, length + 1);

  for (unsigned int i = 0; i < length; i++) {
    slave[i] = (char)payload[i];
  }

  if (strcmp(topic, MQTT_HAS_SLAVE_AVAILABLE_TOPIC) == 0) {
    Serial.printf("Item adicionando na lista:  %s \n", slave);
    manageSlaves->add(slave);
  }
  for (const std::string &sleave : manageSlaves->getAllSleave()) {

    if (strcmp(topic, sleave.c_str())) {
      Serial.printf("-->> sleave: %s \n", sleave.c_str());

      Serial.print("-->> Message:");
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
      }
      Serial.println();
    }
  }

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
