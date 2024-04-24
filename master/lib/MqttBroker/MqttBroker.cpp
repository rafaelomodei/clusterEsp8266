#include "MqttBroker.h"

WiFiClient espClient;
PubSubClient client(espClient);

MqttBroker::MqttBroker(const char *server, int port, const char *userName, const char *password, const char *clientId, const char *outTopic, const char *inTopic)
{
    mqttClientId = clientId;
    mqttServer = server;
    mqttUsername = userName;
    mqttPassword = password;
    mqttOutTopic = outTopic;
    mqttInTopic = inTopic;
    mqttPort = port;
}

void MqttBroker::callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

boolean MqttBroker::reconnect()
{

    if (!client.connect(mqttClientId))
    {
        Serial.printf("Falha ao se conectar [ %s ]\n", mqttClientId);
        return client.connected();
    }

    Serial.printf("Conectado com sucesso [ %s ]\n", mqttClientId);

    return client.connected();
}

void MqttBroker::setup()
{

    const int port = 1883;

    client.setServer(mqttServer, port);
    client.setCallback(MqttBroker::callback);
}

void MqttBroker::loop()
{
    if (!client.connected())
        reconnect();

    client.loop();
}

void MqttBroker::publish(const char *topic, const char *payload)
{
    client.publish(topic, payload);
}

void MqttBroker::subscribe(const char *topic)
{
    client.subscribe(topic);
}
