#include <stdexcept>
#include <iostream>
#include <cstring>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Invalid count of arguments";
      return 1;
    }
    int task = 0;
    try
    {
      size_t pos = 0;
      task = std::stoi(argv[1], &pos);
      if (pos != std::strlen(argv[1]))
      {
        std::cerr << "Task number hasn't provided";
        return 1;
      }

    }
    catch (const std::invalid_argument &ex)
    {
      std::cerr << "Task number hasn't provided";
      return 1;
    }
    catch (const std::out_of_range &ex)
    {
      std::cerr << "Task number is too large";
      return 1;
    }
    switch (task)
    {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        std::cerr << "Invalid number of the task";
        return 1;
    }
  }
  catch (const std::exception &ex)
  {
    std::cerr << ex.what();
    return 1;
  }
  return 0;
}
