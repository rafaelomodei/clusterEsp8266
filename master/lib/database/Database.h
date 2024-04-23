#ifndef DATABASE_H
#define DATABASE_H

#include <stdlib.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define LIST_SIZE 10 // Tamanho do array de retorno da API
#define BASE_URL "https://cluster-esp8266.vercel.app/"

class Database
{

  HTTPClient http;

public:
  Database();
  JsonDocument getUnorderedList(const int page);
};

#endif