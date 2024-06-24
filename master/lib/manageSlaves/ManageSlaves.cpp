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
  queueAvailableSlaves.push(idSlave);
}

// Adicionar um novo Slave
void ManageSlaves::addSlavesToQueue(const char *idSlave) {

  if (queueSlaves.empty()) {
    queueSlaves.push_back({idSlave, false});
  }

  auto iterator = std::find_if(queueSlaves.begin(), queueSlaves.end(), [idSlave](const Slave &s) {
    return s.id == idSlave;
  });

  if (iterator == queueSlaves.end()) {
    ManageSlaves *manageSlaves = ManageSlaves::getInstance();
    queueSlaves.push_back({idSlave, false});

    // Atualize o iterador se você estiver adicionando um novo elemento
    // iterator = std::find(queueSlaves.begin(), queueSlaves.end(), idSlave);
  }
}

void ManageSlaves::showInfo() {
  // Serial.println("[ INFO ] - Imprimindo lista de slaves disponiveis: ");

  std::queue<std::string> queueTemp = queueAvailableSlaves;

  while (!queueAvailableSlaves.empty()) {
    // Serial.printf("%s | ", queueAvailableSlaves.front().c_str());
    queueAvailableSlaves.pop();
  }

  // Serial.println("-----------------------");
}

// Retorna o proximo Slave
std::string ManageSlaves::get() {

  std::string slave = queueAvailableSlaves.front();
  queueAvailableSlaves.pop();
  return slave;
}

// Retorna a lista de Slaves
std::vector<std::string> ManageSlaves::getAllSleave() {

  std::vector<std::string> slaveIds;
  for (const auto &slave : queueSlaves) {
    slaveIds.push_back(slave.id);
  }
  return slaveIds;
}

// Retorna os sleave que o master não está inscrito
std::vector<Slave> ManageSlaves::getNonSubscribableSlaves() {
  std::vector<Slave> nonSubscribableSlaves;
  for (const auto &slave : queueSlaves) {
    if (!slave.isSubscribe) {
      nonSubscribableSlaves.push_back(slave);
    }
  }
  return nonSubscribableSlaves;
}

void ManageSlaves::updateSlaveSubscription(const char *idSlave) {
  // Serial.println("[ INFO ] - Atualizando a fila de sleave inscrito");

  for (auto &slave : queueSlaves) {
    if (slave.id == idSlave) {
      slave.isSubscribe = true;
      break;
    }
  }
}
