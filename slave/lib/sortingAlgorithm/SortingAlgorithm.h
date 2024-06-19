#ifndef BUCKETSORT_H
#define BUCKETSORT_H

#include <Arduino.h>
#include <iostream>
#include <vector>

std::vector<float> bucketSort(const std::vector<float> &arr);
String             floatVectorToString(const std::vector<float> &vec);
void               insertionSort(std::vector<float> &bucket);

#endif // BUCKETSORT_H