#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>

String convertBucketsToJson(const std::vector<std::vector<int>> &buckets);

#endif // HELPERS_H