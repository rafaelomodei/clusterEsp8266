#ifndef MQTT_BROKER_H
#define MQTT_BROKER_H

#ifndef MQTT_HAS_SLAVE_AVAILABLE_TOPIC
#define MQTT_HAS_SLAVE_AVAILABLE_TOPIC "HAS_SLEAVE_AVAILABLE"
#endif

#include <PubSubClient.h>
#include <WiFi.h>

#include "Database.h"
#include "ManageSlaves.h"
#include "Helpers.h"

#define MQTT_MAX_BUFFER_SIZE 2048

typedef struct {
  const char *server;
  const char *userName;
  const char *password;
  const char *clientId;
  const char *outTopic;
  const char *inTopic;
  const int   port;

} MQTT_BROKER;

class MqttBroker {
private:
  const char *mqttServer;
  const char *mqttUsername;
  const char *mqttPassword;
  const char *mqttClientId;
  const char *mqttOutTopic;
  const char *mqttInTopic;
  const int  *mqttPort;

public:
  MqttBroker(MQTT_BROKER params);
  boolean     reconnect();
  void        setup();
  void        loop();
  void        publish(const char *topic, const char *payload);
  void        subscribe(const char *topic);
  static void callback(char *topic, byte *payload, unsigned int length);
};

#endif