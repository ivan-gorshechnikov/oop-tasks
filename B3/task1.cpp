#include <string>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "phone-interface.hpp"
#include "parser.hpp"

void task1(std::istream &input, std::ostream &output)
{
  using in = std::istream_iterator<QuotedCommandType>;
  PhoneInterface bookInterface;
  QuotedCommandType command;
  std::for_each(in(input), in(), [&](const QuotedCommandType& command)
  {
    command.commandType(bookInterface, output);
  });

  if (!input.eof())
  {
    throw std::runtime_error("Error while reading from stream");
  }
  input.clear();
}
