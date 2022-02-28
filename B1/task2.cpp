#include <fstream>
#include <memory>
#include <vector>
#include "print.hpp"

void task2(const char* file)
{
  if (!file)
  {
    throw std::invalid_argument("Name of file is nullptr");
  }
  std::ifstream fin(file);
  if (!fin.is_open())
  {
    throw std::ios_base::failure("");
  }
  if (fin.peek() == EOF)
  {
    return;
  }
  size_t size = 10;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char *>(malloc(size)), &free);

  size_t count = 0;
  while (!fin.eof())
  {
    fin.read(&array[count], size - count);
    count += fin.gcount();
    if (size == count)
    {
      size *= 2;
      std::unique_ptr<char[], decltype(&free)> tempArray(static_cast<char *>(realloc(array.get(), size)), &free);
      if (!tempArray)
      {
        throw std::runtime_error("Can't reallocate memory");
      }
      array.release();
      std::swap(array, tempArray);
    }
  }
  std::vector<char> vector(array.get(), array.get() + count);
  std::cout.write(vector.data(), vector.size());

}
