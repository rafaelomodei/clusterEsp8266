#include "Database.h"

Database::Database() {}

JsonDocument Database::getUnorderedList(const int page) {
  String       url = String(BASE_URL) + "unorderedList";
  JsonDocument doc;

  http.begin(url);
  int httpCode = http.GET();

  Serial.print("Code: ");
  Serial.println(httpCode);

  if (httpCode == 200) {
    String payload = http.getString();

    // Deserializar a resposta da API para o objeto JSON
    deserializeJson(doc, payload);
  } else
    Serial.println("Erro ao fazer solicitação à API");
  http.end();

  return doc;
}