#ifndef MANAGE_SLAVES_H
#define MANAGE_SLAVES_H

#include <Arduino.h>
#include <queue>
#include <string>

#define QUEUE_LENGTH 3
#define SLAVE_STATUS_SIZE sizeof(SLAVE_STATUS)

class ManageSlaves {
private:
  static ManageSlaves    *instance;
  std::queue<std::string> queueAvailableSlaves;

public:
  ManageSlaves();
  static ManageSlaves *getInstance();
  bool                 hasSlaveAvailable();
  void                 add(const char *status);
  std::string          get();
  void                 showInfo();
};

#endif
