#include "ManageTime.h"

ManageTime::ManageTime() {}
ManageTime *ManageTime::instance = nullptr;

ManageTime *ManageTime::getInstance() {
  // Se a instância ainda não existir, cria uma nova
  if (instance == nullptr) {
    instance = new ManageTime();
  }
  return instance;
}

void ManageTime::recordTime(StepTime step, String espId) {
  Serial.print("[ INFO ] - Registrando o tempo ");

    timeline.push_back({espId,
                      step,
                      12});
}

unsigned long getTimeUnix() {
  String       url = "http://worldtimeapi.org/api/timezone/Etc/UTC"; // API para obter o tempo
  HTTPClient   http;
  JsonDocument doc;

  Serial.printf("[ INFO ] - URL: [ %S ] StatusCode: ", url.c_str());

  http.begin(url);
  int httpCode = http.GET();

  Serial.println(httpCode);

  if (httpCode == 200) {
    String payload = http.getString();

    // Deserializar a resposta da API para o objeto JSON
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("[ ERRO ] - Erro ao deserializar JSON: ");
      Serial.println(error.f_str());
      getTimeUnix();
    }

  } else {
    Serial.println("[ ERRO ] - Erro ao fazer solicitação à API... Tentando novamente");
    getTimeUnix();
  }
  http.end();

  return doc["unixtime"];
}