#ifndef B1_GET_ORIENTATION_HPP
#define B1_GET_ORIENTATION_HPP
#include <cstring>
#include <stdexcept>
#include "tasks.hpp"
SortingOrientation getOrientation(const char* orientation)
{
  if (std::strcmp(orientation, "ascending") == 0)
  {
    return SortingOrientation::ASCENDING;
  }
  else if (std::strcmp(orientation, "descending") == 0)
  {
    return SortingOrientation::DESCENDING;
  }
  else
  {
    throw std::invalid_argument("Invalid orientation\n");
  }
}
#endif
