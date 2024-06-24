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

  ManageSlaves *manageSlaves = ManageSlaves::getInstance();
  Database     *db           = Database::getInstance();

  // Converte o payload para uma String
  String slave = "";
  for (unsigned int i = 0; i < length; i++) {
    slave += (char)payload[i];
  }

  if (strcmp(topic, MQTT_HAS_SLAVE_AVAILABLE_TOPIC) == 0) {
    // Serial.printf("[ INFO ] - ESP adicionando na lista:  %s \n\r", slave.c_str());

    manageSlaves->add(slave.c_str());

    // Concatena a string de sufixo
    String suffix = "_RESPONSE";
    slave += suffix;
    manageSlaves->addSlavesToQueue(slave.c_str());
  }

  // Serial.printf("[ ### ] - Topico:  ");
  // Serial.println(topic);

  for (const std::string &sleave : manageSlaves->getAllSleave()) {

    std::size_t sizeQueueSlaves = manageSlaves->getAllSleave().size();

    if (strcmp(topic, sleave.c_str()) == 0) {
      // Serial.printf("[ INFO ] - Sleave: %s \n\r", sleave.c_str());
      // Serial.print("[ INFO:RECEBIDO ] - Message: ");
      // Serial.println();

      String data = "";
      for (unsigned int i = 0; i < length; i++) {
        data += (char)payload[i];
      }

      if (!data.isEmpty())
        db->postBucketList(data);
    }
  }
}

boolean MqttBroker::reconnect() {

  if (!client.connect(mqttClientId)) {
    // Serial.printf("[ ERRO ] - Falha ao se conectar [ %s ]\n\r", mqttClientId);
    return client.connected();
  }

  client.subscribe(MQTT_HAS_SLAVE_AVAILABLE_TOPIC);
  // Serial.printf("[ INFO ] - Conectado com sucesso [ %s ]\n\r", mqttClientId);

  return client.connected();
}

void MqttBroker::setup() {

  const int port = 1883;

  client.setServer(mqttServer, port);
  client.setBufferSize(MQTT_MAX_BUFFER_SIZE);
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
