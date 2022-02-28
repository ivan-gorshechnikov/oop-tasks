#include <vector>
#include <forward_list>
#include "sort.hpp"
#include "access.hpp"
#include "print.hpp"
#include "tasks.hpp"

void task1(SortingOrientation compare)
{
  std::vector<int> vectorByBrackets;
  int number;
  while (std::cin >> number)
  {
    vectorByBrackets.push_back(number);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Error by reading data");
  }

  if (vectorByBrackets.empty())
  {
    return;
  }
  std::vector<int> vectorByAt(vectorByBrackets);
  std::forward_list<int> listByIterator(vectorByBrackets.begin(), vectorByBrackets.end());
  sort<AccessByBrackets>(vectorByBrackets, compare);
  sort<AccessByAt>(vectorByAt, compare);
  sort<AccessByIterator>(listByIterator, compare);

  print(vectorByBrackets);
  print(vectorByAt);
  print(listByIterator);
}
