#ifndef MANAGE_SLAVES_H
#define MANAGE_SLAVES_H

#include <freertos/FreeRTOS.h>
#include <queue>

#include <MqttBroker.h>

typedef struct {
  const char *id_slave;
  const char *status;
} SLAVE;

#define QUEUE_LENGTH 3
#define SLAVE_STATUS_SIZE sizeof(SLAVE_STATUS)

class ManageSlaves {
private:
  MqttBroker       *mqtt;
  std::queue<SLAVE> queueAvailableSlaves;

public:
  ManageSlaves(MqttBroker *mqttClients);
  boolean hasSlaveAvailable();
  void    add(SLAVE status);
  SLAVE   get();
};

#endif
