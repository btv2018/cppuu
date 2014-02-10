

#include <iostream>
#include <algorithm>
#include "summation.h"
#include "ostream_operators.h"


void Assert(float result, const std::vector<float>& numbers) {
  auto copy = numbers;
  float sum = AccurateSum(copy);
  if (sum == result) {
    std::cerr << "  OK: expected: " << result << " \tactual: " << sum << " \tfor data: " << numbers << std::endl;
  } else {
    std::cerr << "FAIL: expected: " << result << " \tactual: " << sum << " \tfor data: " << to_string(numbers) << std::endl;
  }
}


int main() {
  
  std::vector<float> v0{};
  std::vector<float> v1{34.3f};
  std::vector<float> v2{1.0f, 56.0f};
  std::vector<float> v3{4.3f, 1.0f, 56.0f};
  std::vector<float> v4{4.3E-10f, 1.0E5f, 56.0f};
  std::vector<float> v5(100, 100);
 
  Assert(0.0f, v0);
  Assert(v1[0], v1);
  Assert(v2[0] + v2[1], v2);
  Assert(std::accumulate(v3.begin(), v3.end(), 0.0f), v3);
  Assert(std::accumulate(v4.begin(), v4.end(), 0.0f), v4);
  Assert(std::accumulate(v5.begin(), v5.end(), 0.0f), v5);
  

  return 0;
}



