#include <iostream>
#include <stdexcept>
#include "task.hpp"

int main()
{
  try
  {
    task(std::cin, std::cout);
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what();
    return 1;
  }
  return 0;
}
