#include "Database.h"

Database::Database() {
  currentPageUnordered = 0;
  totalPageUnordered   = -1; // Inicia com -1 para saber que é o status inicial
}
Database *Database::instance = nullptr;

Database *Database::getInstance() {
  // Se a instância ainda não existir, cria uma nova
  if (instance == nullptr) {
    instance = new Database();
  }
  return instance;
}

String Database::getUnorderedList() {
  String       url = String(BASE_URL) + "unorderedList";
  String       jsonString;
  JsonDocument doc;

  Serial.printf("[ INFO ] - URL: [ %S ] StatusCode: ", url.c_str());

  http.begin(url);

  // Adicionar campo no cabeçalho
  http.addHeader("Page", String(currentPageUnordered));

  int httpCode = http.GET();

  Serial.println(httpCode);

  if (httpCode == 200) {
    String payload = http.getString();

    // Deserializar a resposta da API para o objeto JSON
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("[ ERRO ] - Erro ao deserializar JSON: ");
      Serial.println(error.f_str());
    } else {
      // Converter JSON para string
      serializeJson(doc, jsonString);
      currentPageUnordered++;
    }
  } else {
    Serial.println("[ ERRO ] - Erro ao fazer solicitação à API... Tentando novamente");
    Database::getUnorderedList();
  }

  http.end();

  return jsonString;
}

JsonDocument Database::getTotalPage() {
  String       url = String(BASE_URL) + "totalPages";
  String       jsonString;
  JsonDocument doc;

  Serial.printf("[ INFO ] - URL: [%S ] StatusCode: ", url.c_str());

  http.begin(url);
  int httpCode = http.GET();

  Serial.println(httpCode);

  if (httpCode == 200) {
    String payload = http.getString();

    // Deserializar a resposta da API para o objeto JSON
    deserializeJson(doc, payload);
  } else {
    Serial.println("[ ERRO ] - Erro ao fazer solicitação à API... Tentando novamente");
    Database::getTotalPage();
  }

  http.end();

  return doc;
}

void Database::postBucketList(String data) {
  String url = String(BASE_URL) + "bucketList";

  Serial.printf("[ INFO ] - URL: [ %s ] StatusCode: ", url.c_str());

  http.begin(url);

  // Adicionar campo no cabeçalho, se necessário
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(data);

  Serial.println(httpCode);

  if (httpCode == 200) {
    Serial.println("[ INFO ] - Dados enviados com sucesso.");
  } else {
    Serial.println("[ ERRO ] - Erro ao enviar dados para API... Tentando novamente");
    Database::postBucketList(data);
  }

  http.end();
}