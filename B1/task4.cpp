#include <vector>
#include <cstdlib>
#include "sort.hpp"
#include "access.hpp"
#include "print.hpp"

void fillRandom (double* array, int size)
{
  for (int i = 0; i < size; i++)
  {
    array[i] = rand() * 2.0 / (RAND_MAX) - 1.0;
  }
}

void task4 (SortingOrientation compare, int size)
{
  if (size < 0)
  {
    throw std::invalid_argument("Can't be negative size");
  }
  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector);
  sort<AccessByBrackets>(vector, compare);
  print(vector);
}
