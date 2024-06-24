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

String convertBucketsToString(const std::vector<std::vector<int>> &buckets) {
  String result = "[";

  for (size_t i = 0; i < buckets.size(); ++i) {
    result += "{";
    result += "\"id\": " + String(i + 1) + ",";
    result += "\"list\": [";

    for (size_t j = 0; j < buckets[i].size(); ++j) {
      result += String(buckets[i][j]);
      if (j < buckets[i].size() - 1) {
        result += ",";
      }
    }

    result += "]";
    if (i < buckets.size() - 1) {
      result += "},";
    } else {
      result += "}";
    }
  }

  result += "]";
  return result;
}

std::string convertToJson(const std::vector<std::vector<int>> &data) {
  std::ostringstream oss;
  oss << "[";

  for (size_t i = 0; i < data.size(); ++i) {
    oss << "{\"id\":" << (i + 1) << ",\"list\":[";
    for (size_t j = 0; j < data[i].size(); ++j) {
      oss << data[i][j];
      if (j < data[i].size() - 1) {
        oss << ",";
      }
    }
    oss << "]}";
    if (i < data.size() - 1) {
      oss << ",";
    }
  }

  oss << "]";
  return oss.str();
}