// Função para converter os buckets em JSON
#include "Helpers.h"

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

String createTimeLineJson(const String &espId, const String &StepTime) {
  DynamicJsonDocument doc(1024); // Aumente o tamanho se necessário

  unsigned long unixtime = getTimeUnix();

  JsonArray  timeLineArray   = doc.createNestedArray("timeLine");
  JsonObject timeLineObject  = timeLineArray.createNestedObject();
  timeLineObject["espId"]    = espId;
  timeLineObject["StepTime"] = StepTime;
  timeLineObject["unixtime"] = unixtime;

  // Converte o JSON document para uma string
  String output;
  serializeJson(doc, output);

  return output;
}
