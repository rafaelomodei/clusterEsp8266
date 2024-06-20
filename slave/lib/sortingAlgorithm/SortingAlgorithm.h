#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <Arduino.h>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> bucketSort(std::vector<int> &arr);
String                        floatVectorToString(const std::vector<int> &vec);
void                          insertionSort(std::vector<int> &bucket);
void                          printIntArray(const std::vector<int> &intArray);

#endif // BUCKETSORT_H