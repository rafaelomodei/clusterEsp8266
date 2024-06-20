#include "header.h"

int currentPageUnordered = 0;

ManageSlaves *manageSlaves = ManageSlaves::getInstance();

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

Database db;

void setup() {
  Serial.begin(115200);

  Wifi(WIFI_SSID, WIFI_PASSWORD);

  // Configuração inicial do MQTT
  mqttBroker.setup();
}

void loop() {
  mqttBroker.loop();

  if (manageSlaves->hasSlaveAvailable()) {
    std::string topicSleave = manageSlaves->get();

    JsonDocument totalPage          = db.getTotalPage();
    String       totalPageUnordered = totalPage["totalPageUnordered"];

    if (currentPageUnordered <= atoi(totalPageUnordered.c_str())) {
      String message = db.getUnorderedList(currentPageUnordered);
      currentPageUnordered++;

      Serial.printf("Total de paginas de itens desordenados: %s \n", totalPageUnordered);
      Serial.printf("Enviando dados para o ESP: [ %s ] \n", topicSleave.c_str());
      Serial.printf("Mensagem: %s  \n", message.c_str());
      Serial.println("-----------------------");

      mqttBroker.publish(topicSleave.c_str(), message.c_str());
    }
  }
}
