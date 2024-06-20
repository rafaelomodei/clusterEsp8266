#include "SortingAlgorithm.h"
#include <ArduinoJson.h>
#include <algorithm>

// Função para encontrar o máximo valor no array
int getMaxValue(const std::vector<int> &arr) {
  return *std::max_element(arr.begin(), arr.end());
}

// Função para o algoritmo bucket sort
std::vector<std::vector<int>> bucketSort(std::vector<int> &arr) {

  const int TOTAL_BUCKET = 10;

  int n = arr.size();

  int maxValue    = getMaxValue(arr);
  int bucketCount = maxValue / TOTAL_BUCKET + 1;

  std::vector<std::vector<int>> buckets(bucketCount);

  // Distribui os elementos nos buckets
  for (int i = 0; i < n; i++) {
    int bucketIndex = arr[i] / TOTAL_BUCKET;
    buckets[bucketIndex].push_back(arr[i]);
  }

  // Ordena cada bucket e junta os resultados
  int index = 0;
  for (int i = 0; i < bucketCount; i++) {
    std::sort(buckets[i].begin(), buckets[i].end());
    for (int j = 0; j < buckets[i].size(); j++) {
      arr[index++] = buckets[i][j];
    }
  }

  return buckets;
}

void insertionSort(std::vector<int> &bucket) {
  int n = bucket.size();
  for (int i = 1; i < n; ++i) {
    float key = bucket[i];
    int   j   = i - 1;
    while (j >= 0 && bucket[j] > key) {
      bucket[j + 1] = bucket[j];
      j             = j - 1;
    }
    bucket[j + 1] = key;
  }
}

// Função para converter um vetor de floats para uma string
String floatVectorToString(const std::vector<int> &vec) {
  Serial.println("FloatVectorToString");
  String result = "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    result += String(vec[i]);
    Serial.print(vec[i]);
    if (i < vec.size() - 1) {
      result += ", ";
    }
  }
  result += "]";
  return result;
}

// Função para imprimir os valores do vetor de inteiros
void printIntArray(const std::vector<int> &intArray) {
  for (int value : intArray) {
    Serial.println(value);
  }
}
