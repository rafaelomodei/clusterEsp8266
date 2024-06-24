// Função para converter os buckets em JSON
#include "Helpers.h"

String convertBucketsToJson(const std::vector<std::vector<int>> &buckets) {
  DynamicJsonDocument doc(2048); // Aumente o tamanho se necessário
  JsonArray           jsonBucketList = doc.createNestedArray("bucketList");

  Serial.println("Convertendo buckets em json");

  for (int i = 0; i < buckets.size(); i++) {
    JsonObject bucketObject = jsonBucketList.createNestedObject();
    bucketObject["id"]      = i + 1;
    JsonArray jsonList      = bucketObject.createNestedArray("list");
    for (int num : buckets[i]) {
      jsonList.add(num);
    }
  }

  // Converte o JSON document para uma string
  String output;
  serializeJson(doc, output);

  return output;
}
