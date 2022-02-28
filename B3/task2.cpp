#include <iostream>
#include <algorithm>
#include "container-factorial.hpp"
void task2(std::ostream &output)
{
  ContainerFactorial factorial;

  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(output, " "));
  output << '\n';

  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(output, " "));
  output << '\n';
}
