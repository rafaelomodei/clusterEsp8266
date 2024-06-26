#ifndef DATABASE_H
#define DATABASE_H

#include "Helpers.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <stdlib.h>

#define LIST_SIZE 10 // Tamanho do array de retorno da API
#define BASE_URL "http://192.168.30.105:3000/"

class Database {

  HTTPClient       http;
  static Database *instance;

public:
  int currentPageUnordered;
  int totalPageUnordered;

  Database();
  static Database *getInstance();
  String           getUnorderedList(String StepTime);
  JsonDocument     getTotalPage();
  void             postBucketList(String data, String StepTime);
  void             postRecordTime(String data);
};

#endif