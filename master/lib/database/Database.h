#ifndef DATABASE_H
#define DATABASE_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <stdlib.h>

#define LIST_SIZE 10 // Tamanho do array de retorno da API
#define BASE_URL "http://beige-needles-deny.loca.lt/"

class Database {

  HTTPClient http;

public:
  Database();
  String       getUnorderedList(const int page);
  JsonDocument getTotalPage();
};

#endif