#include <vector>
#include "print.hpp"

void task3() {
  std::vector<int> vector;
  int number = 0;
  while (std::cin >> number)
  {
    if (number == 0)
    {
      break;
    }
    vector.push_back(number);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("");
  }

  if (vector.empty())
  {
    return;
  }

  if (number != 0)
  {
    throw std::invalid_argument("Last number must be zero");
  }

  switch (vector.back())
  {
    case 1:
      {
      auto it = vector.begin(); //std::vector<int>::iterator
      while (it != vector.end())
      {
        if ((*it) % 2 == 0)
        {
          it = vector.erase(it);
        }
        else
        {
          it++;
        }
      }
      break;
    }
    case 2:
    {
      auto it = vector.begin(); //std::vector<int>::iterator
      while (it != vector.end())
      {
        if ((*it) % 3 == 0)
        {
          it = vector.insert(it + 1, 3, 1);
          it += 3;
        }
        else
        {
          it++;
        }
      }
      break;
    }
    default:
    {
      break;
    }
  }
  print(vector);
}
