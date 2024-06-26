#ifndef HELPERS_H
#define HELPERS_H

#include <ArduinoJson.h>
#include <vector>

#include <iostream>
#include <sstream>
#include <string>

#include <HTTPClient.h>

String createTimeLineJson(const String &espId, const String &StepTime);
unsigned long getTimeUnix();

#endif // HELPERS_H