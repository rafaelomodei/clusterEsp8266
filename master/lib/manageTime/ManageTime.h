#ifndef MANAGE_TIME_H
#define MANAGE_TIME_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

enum StepTime {
  START,
  END
};

struct Time {
  String        espId;
  StepTime      step;
  unsigned long unixtime;
};

class ManageTime {
private:
  static ManageTime *instance;

public:
  std::vector<Time> timeline;

  ManageTime();
  static ManageTime *getInstance();
  void               recordTime(StepTime step, String espId);
};

#endif
