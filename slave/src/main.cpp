#include "header.h"

// Instancie a classe MQTTBroker
MqttBroker mqttBroker(MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID, MQTT_OUT_TOPIC, MQTT_IN_TOPIC);



void setup() {
  Serial.begin(115200);

  Wifi(WIFI_SSID, WIFI_PASSWORD);

  // Configuração inicial do MQTT

  std::vector<float> arr       = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
  std::vector<float> sortedArr = bucketSort(arr);

  // Serial.println("Sorted array is: " + floatVectorToString(sortedArr));

  mqttBroker.setup();

}

void loop() {
  // Mantenha a conexão MQTT ativa
  mqttBroker.loop();

  // Verificar se tem SERVO disponiveis
  // Se tiver SERVO disponivel, busca os dados na API
  // Via os dados da API para o SERVO

  // Se não tiver servo disponivel, não faz nada
}
