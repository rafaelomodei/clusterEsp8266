#include "esp_timer.h"
#include "header.h"

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

Database *db = Database::getInstance();

void setup() {
  Serial.begin(115200);

  Wifi(WIFI_SSID, WIFI_PASSWORD);

  // Configuração inicial do MQTT
  mqttBroker.setup();
}

void loop() {
  mqttBroker.loop();

  // Caso o mestre ainda não esteja inscrito no topico do sleave, então se inscreve
  if (!manageSlaves->getNonSubscribableSlaves().empty()) {

    Serial.println("[ INFO ] - Inscrevendo nos topicos dos sleaves");

    int sizeNonSubscribableSlaves = manageSlaves->getNonSubscribableSlaves().size();

    for (int i = 0; i < sizeNonSubscribableSlaves; i++) {
      std::string id = manageSlaves->getNonSubscribableSlaves()[i].id;
      Serial.printf("[ INFO ] - Inscrito no topico: %s \n\r", id.c_str());

      mqttBroker.subscribe(id.c_str());
      manageSlaves->updateSlaveSubscription(id.c_str());
    }
  }

  if (manageSlaves->hasSlaveAvailable() && db->totalPageUnordered == -1) {
    JsonDocument totalPage                = db->getTotalPage();
    String       stringTotalPageUnordered = totalPage["totalPageUnordered"];
    db->totalPageUnordered                = atoi(stringTotalPageUnordered.c_str());
  }

  // Busca os dados desordenado na API
  if (manageSlaves->hasSlaveAvailable()) {
    std::string topicSleave = manageSlaves->getSleave();

    if (db->currentPageUnordered <= db->totalPageUnordered) {
      String element = db->getUnorderedList();

      Serial.printf("[ INFO ] - Paginas processadas: %d de %d \n\r", db->currentPageUnordered, db->totalPageUnordered);
      Serial.printf("[ INFO ] - Enviando dados para o ESP: [ %s ] \n\r", topicSleave.c_str());
      Serial.printf("[ INFO ] - Elementos: %s  \n", element.c_str());
      Serial.println("-----------------------");

      // mqttBroker.subscribe(topicSleave.c_str());
      mqttBroker.publish(topicSleave.c_str(), element.c_str());
    }
  }
}
