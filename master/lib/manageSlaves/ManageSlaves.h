#ifndef MANAGE_SLAVES_H
#define MANAGE_SLAVES_H

#include <Arduino.h>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define QUEUE_LENGTH 3
#define SLAVE_STATUS_SIZE sizeof(SLAVE_STATUS)

class ManageSlaves {
private:
  static ManageSlaves     *instance;
  std::vector<std::string> queueSlaves;
  std::queue<std::string>  queueAvailableSlaves;

public:
  ManageSlaves();
  static ManageSlaves     *getInstance();
  bool                     hasSlaveAvailable();
  void                     add(const char *status);
  std::string              get();
  std::vector<std::string> getAllSleave();
  void                     showInfo();
};

#endif
