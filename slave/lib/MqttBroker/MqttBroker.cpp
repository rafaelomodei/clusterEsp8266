#include "MqttBroker.h"
#include "SortingAlgorithm.h"
#include <typeinfo>

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
  String mqttCurrentClientId = "ESP8266_CLIENT_";
  mqttCurrentClientId += String(WiFi.macAddress());

  char *arrayDisordered = (char *)malloc(length + 1);

  // Inicializa a memória alocada com zeros
  memset(arrayDisordered, 0, length + 1);

  for (unsigned int i = 0; i < length; i++) {
    arrayDisordered[i] = (char)payload[i];
  }

  if (strcmp(topic, mqttCurrentClientId.c_str()) == 0) {

    // Remove os colchetes
    char *trimmedArray                     = arrayDisordered + 1;
    trimmedArray[strlen(trimmedArray) - 1] = '\0';

    Serial.print("-> Elementos: ");
    // Converter o array de char para um array de inteiros
    std::vector<int> intArray;
    char            *token = strtok(trimmedArray, ", ");
    while (token != nullptr) {
      Serial.printf(" %s |", token);
      intArray.push_back(atoi(token));
      token = strtok(nullptr, ", ");
    }
    Serial.println();

    std::vector<int> arr = bucketSort(intArray);
    Serial.print("Array ordenado: ");
    printIntArray(arr);

    Serial.printf("Publicando no topico [ %s ]\n", MQTT_HAS_SLAVE_AVAILABLE_TOPIC);
    client.publish(MQTT_HAS_SLAVE_AVAILABLE_TOPIC, mqttCurrentClientId.c_str());
  }

  Serial.printf("Mesagem recebida no topico: ");
  Serial.println(topic);
  Serial.print("Message: ");
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
