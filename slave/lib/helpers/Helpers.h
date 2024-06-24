#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>

#include <iostream>
#include <sstream>
#include <string>

String      convertBucketsToJson(const std::vector<std::vector<int>> &buckets);
String      convertBucketsToString(const std::vector<std::vector<int>> &buckets);
std::string convertToJson(const std::vector<std::vector<int>> &data);

#endif // HELPERS_H