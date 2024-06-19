#ifndef DATABASE_H
#define DATABASE_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <stdlib.h>

#define LIST_SIZE 10 // Tamanho do array de retorno da API
#define BASE_URL "https://cluster-esp8266.vercel.app/unorderedList"

class Database {

  HTTPClient http;

public:
  Database();
  JsonDocument getUnorderedList(const int page);
};

#endif