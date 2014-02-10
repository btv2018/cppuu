
#include "summation.h"
#include <algorithm>


float AccurateSum(std::vector<float>& numbers) {
  std::sort(numbers.begin(), numbers.end());
  return AccurateSumSorted(numbers.begin(), numbers.end());
}



