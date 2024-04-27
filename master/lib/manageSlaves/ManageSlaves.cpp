#include "ManageSlaves.h"

ManageSlaves::ManageSlaves() {}

// Se tiver itens na fila, é pq tem slave disponível
bool ManageSlaves::hasSlaveAvailable() {
  return !queueAvailableSlaves.empty();
}

// Adicionar um novo Slave
void ManageSlaves::add(const char *idSlave) {

  Serial.println("Adicionando esp a lista");

  queueAvailableSlaves.push(idSlave);
}

// Retorna o proximo Slave
std::string ManageSlaves::get() {

  std::string slave = queueAvailableSlaves.front();
  queueAvailableSlaves.pop();
  return slave;
}
