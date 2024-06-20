#include "ManageSlaves.h"

// Inicializando a instância estática como nula

ManageSlaves::ManageSlaves() {};
ManageSlaves *ManageSlaves::instance = nullptr;

ManageSlaves *ManageSlaves::getInstance() {
  // Se a instância ainda não existir, cria uma nova
  if (instance == nullptr) {
    instance = new ManageSlaves();
  }
  return instance;
}

// Se tiver itens na fila, é pq tem slave disponível
bool ManageSlaves::hasSlaveAvailable() {
  return !queueAvailableSlaves.empty();
}

// Adicionar um novo Slave
void ManageSlaves::add(const char *idSlave) {

  Serial.println("Adicionando ESP a lista");
  queueAvailableSlaves.push(idSlave);

  auto iterator = std::find(queueSlaves.begin(), queueSlaves.end(), idSlave);
  if (queueSlaves.empty())
    queueSlaves.push_back(idSlave);

  for (const std::string &sleave : queueSlaves) {
    if (iterator != queueSlaves.end())
      queueSlaves.push_back(idSlave);
  }
}

void ManageSlaves::showInfo() {
  Serial.println("Imprimindo lista de slaves disponíveis: ");

  std::queue<std::string> queueTemp = queueAvailableSlaves;

  while (!queueAvailableSlaves.empty()) {
    Serial.printf("%s; ", queueAvailableSlaves.front().c_str());
    queueAvailableSlaves.pop();
  }

  Serial.println("-----------------------");
}

// Retorna o proximo Slave
std::string ManageSlaves::get() {

  std::string slave = queueAvailableSlaves.front();
  queueAvailableSlaves.pop();
  return slave;
}

// Retorna a lista de Slaves
std::vector<std::string> ManageSlaves::getAllSleave() {

  return queueSlaves;
}
