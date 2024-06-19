#include "SortingAlgorithm.h"
#include <algorithm>

std::vector<float> bucketSort(const std::vector<float> &arr) {
  int n = arr.size();
  if (n <= 0)
    return arr;

  // 1. Criar n baldes vazios
  std::vector<std::vector<float>> buckets(n);

  // 2. Colocar elementos nos baldes correspondentes
  for (int i = 0; i < n; i++) {
    int bucketIndex = n * arr[i]; // índice do balde
    buckets[bucketIndex].push_back(arr[i]);
  }

  // 3. Ordenar individualmente cada balde
  for (int i = 0; i < n; i++) {
    insertionSort(buckets[i]);
  }

  // 4. Concatenar todos os baldes em um vetor de saída
  std::vector<float> sortedArr;
  for (int i = 0; i < n; i++) {
    for (size_t j = 0; j < buckets[i].size(); j++) {
      sortedArr.push_back(buckets[i][j]);
    }
  }

  return sortedArr;
}

void insertionSort(std::vector<float> &bucket) {
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
String floatVectorToString(const std::vector<float> &vec) {
  String result = "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    result += String(vec[i]);
    if (i < vec.size() - 1) {
      result += ", ";
    }
  }
  result += "]";
  return result;
}