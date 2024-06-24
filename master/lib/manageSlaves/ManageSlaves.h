#ifndef MANAGE_SLAVES_H
#define MANAGE_SLAVES_H

#include <Arduino.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define QUEUE_LENGTH 3
#define SLAVE_STATUS_SIZE sizeof(SLAVE_STATUS)

struct Slave {
  std::string id;
  bool        isSubscribe;
};

class ManageSlaves {
private:
  static ManageSlaves    *instance;
  std::vector<Slave>      queueSlaves;
  std::queue<std::string> queueAvailableSlaves;

public:
  ManageSlaves();
  static ManageSlaves     *getInstance();
  void                     showInfo();
  bool                     hasSlaveAvailable();
  void                     add(const char *status);
  void                     addSlavesToQueue(const char *idSlave);
  void                     updateSlaveSubscription(const char *idSlave);
  std::string              get();
  std::vector<std::string> getAllSleave();
  std::vector<Slave>       getNonSubscribableSlaves();
};

#endif
