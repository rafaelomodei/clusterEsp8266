#include "ManageSlaves.h"

ManageSlaves::ManageSlaves(MqttBroker *mqttClients) { mqtt = mqttClients; }

// Se tiver itens na fila, é pq tem slave disponível
boolean ManageSlaves::hasSlaveAvailable() {
  return !queueAvailableSlaves.empty();
}

// Adicionar um novo Slave
void ManageSlaves::add(SLAVE slave) { queueAvailableSlaves.push(slave); }

// Retorna o proximo Slave
SLAVE ManageSlaves::get() {

  const SLAVE slave = queueAvailableSlaves.front();
  queueAvailableSlaves.pop();
  return slave;
}
