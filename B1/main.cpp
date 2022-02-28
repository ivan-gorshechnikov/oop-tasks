#include <stdexcept>
#include <iostream>
#include <ctime>
#include "tasks.hpp"
#include "get-orientation.hpp"
int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Incorrect count of arguments";
      return 1;
    }
    int task = 0;
    try
    {
      task = std::stoi(argv[1]);
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
    switch (task) {
        case 1:
            if (argc != 3) {
                std::cerr << "Incorrect count of arguments";
                return 1;
            }
            SortingOrientation orientation;
            orientation = getOrientation(argv[2]);
            task1(orientation);
            break;
        case 2:
            if (argc != 3) {
                std::cerr << "Incorrect count of arguments";
                return 1;
            }
            task2(argv[2]);
            break;
        case 3:
            if (argc != 2) {
                std::cerr << "Incorrect count of arguments";
                return 1;
            }
            task3();
            break;
        case 4: {
            if (argc != 4) {
                std::cerr << "Incorrect count of arguments";
                return 1;
            }
            int size = 0;
            try {
                size = std::stoi(argv[3]);
            }
            catch (const std::invalid_argument &ex) {
                std::cerr << "Task number hasn't provided";
                return 1;
            }
            catch (const std::out_of_range &ex) {
                std::cerr << "Task number is too large";
                return 1;
            }
            orientation = getOrientation(argv[2]);
            std::srand(time(0));
            task4(orientation, size);
            break;
        }
        default:
            std::cerr << "Incorrect number of task";
            return 1;
    }
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error";
    return 1;
  }
  return 0;
}
