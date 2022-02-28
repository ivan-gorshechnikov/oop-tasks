#ifndef B1_PRINT_HPP
#define B1_PRINT_HPP

#include <iostream>

template<class T>
void print(T &container)
{
  typename T::iterator begin = container.begin();
  typename T::iterator end = container.end();
  for (typename T::iterator iter = begin; iter != end; ++iter)
  {
    std::cout << *iter << " ";
  }
  std::cout << "\n";
}
#endif
