#include <list>
#include <iostream>
#include <stdexcept>
#include <ostream>

void task2()
{
  std::list<int> list;
  unsigned int count = 0;
  int number;
  const int minNumber = 1;
  const int maxNumber = 20;
  const int maxSize = 20;
  while (std::cin >> number)
  {
    if ((number > maxNumber) || (number < minNumber))
    {
      throw std::runtime_error("Number is out of range");
    }
    count++;
    if (count > maxSize)
    {
      throw std::invalid_argument("Too much numbers");
    }
    list.push_back(number);
  }
  if (!std::cin.eof())
  {
    throw std::invalid_argument("Incorrect input data");
  }
  if (list.empty())
  {
    return;
  }
  auto i = list.begin();
  auto j = list.end();
  j--;
  while (i != j)
  {
    std::cout << *(i++);
    if (i == j)
    {
      std::cout << " " << *i << "\n";
      return;
    }
    std::cout << " " << *(j--) << " ";
  }
  std::cout << *i << "\n";
}
