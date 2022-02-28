#include <istream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"


void task(std::istream& input, std::ostream& output)
{
  using in = std::istream_iterator<data_struct_t>;
  using out = std::ostream_iterator<data_struct_t>;
  std::vector<data_struct_t> vector{in(input), in()};
  if ((!input.eof()) && (input.fail()))
  {
    throw std::invalid_argument("Error by reading data!");
  }
  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), out(output, "\n"));
}
