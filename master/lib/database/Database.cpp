#include "Database.h"

Database::Database() {}

String Database::getUnorderedList(const int page) {
  String       url = String(BASE_URL) + "unorderedList";
  String       jsonString;
  JsonDocument doc;

  Serial.printf("URL: [%S ] StatusCode: \n", url.c_str());

  http.begin(url);

  // Adicionar campo no cabeçalho
  http.addHeader("Page", String(page));

  int httpCode = http.GET();

  Serial.println(httpCode);

  if (httpCode == 200) {
    String payload = http.getString();

    // Deserializar a resposta da API para o objeto JSON
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.print("Erro ao deserializar JSON: ");
      Serial.println(error.f_str());
    } else {
      // Converter JSON para string
      serializeJson(doc, jsonString);
    }
  } else
    Serial.println("Erro ao fazer solicitação à API");
  http.end();

  return jsonString;
}

JsonDocument Database::getTotalPage() {
  String       url = String(BASE_URL) + "totalPages";
  String       jsonString;
  JsonDocument doc;

  Serial.printf("URL: [%S ] StatusCode: ", url.c_str());

  http.begin(url);
  int httpCode = http.GET();

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