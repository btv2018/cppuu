
#ifndef SUMMATION_H
#define SUMMATION_H

#include <vector>

float AccurateSum(std::vector<float>& numbers);

template<typename It>
float PopMin(It& begin1, It end1, It& begin2, It end2) {
  if (begin1 == end1 && begin2 == end2) {
    return 0.0f;
  } else if (begin1 == end1) {
    return *(begin2++);
  } else if (begin2 == end2) {
    return *(begin1++);
  } else {
    return *begin1 < *begin2 ? *(begin1++) : *(begin2++);
  }
}

template<typename It>
float AccurateSumSorted(It begin, It end) {
  if (begin == end) {
    return 0.0f;
  }
  It second = begin;
  ++second;
  if (second == end) {
    return *begin;
  }

  It buffer_begin = begin;
  It buffer_end = begin;
  while (begin != end) {
    float min1 = PopMin(begin, end, buffer_begin, buffer_end);
    float min2 = PopMin(begin, end, buffer_begin, buffer_end);
    *buffer_end = min1 + min2;
    ++buffer_end;
  }
  return AccurateSumSorted(buffer_begin, buffer_end);
}


#endif // SUMMATION_H

