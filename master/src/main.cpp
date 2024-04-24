#include "header.h"

// Instancie a classe MQTTBroker
MqttBroker mqttBroker(MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID, MQTT_OUT_TOPIC, MQTT_IN_TOPIC);

void setup()
{
    Serial.begin(115200);

    Wifi(WIFI_SSID, WIFI_PASSWORD);

    Database db;

    // Configuração inicial do MQTT
    mqttBroker.setup();
    // Inscreva-se em um tópico (opcional)
    // mqttBroker.subscribe("tópico/teste");

    Serial.print("Data base: ");

    serializeJsonPretty(db.getUnorderedList(1), Serial);
}

void loop()
{
    mqttBroker.loop();

    // Mantenha a conexão MQTT ativa
}
