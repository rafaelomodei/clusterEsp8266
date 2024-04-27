#ifndef MANAGE_SLAVES_H
#define MANAGE_SLAVES_H

#include <Arduino.h>
#include <queue>
#include <string>

#define QUEUE_LENGTH 3
#define SLAVE_STATUS_SIZE sizeof(SLAVE_STATUS)

class ManageSlaves {
private:
  std::queue<std::string> queueAvailableSlaves;

public:
  ManageSlaves();
  bool        hasSlaveAvailable();
  void        add(const char *status);
  std::string get();
};

#endif
