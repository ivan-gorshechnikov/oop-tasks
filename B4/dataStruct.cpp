#include "dataStruct.hpp"
#include <iostream>
#include "stream-guard.hpp"

const char COMMA = ',';
const int MAX_NUMBER = 5;

std::ostream& operator<<(std::ostream& output, const data_struct_t& data)
{
  output << data.key1 << "," << data.key2 << "," << data.str;
  return output;
}

std::istream& skipSpaces(std::istream& input)
{
  while (std::isblank(input.peek()))
  {
    input.get();
  }
  return input;
}

std::istream& operator>>(std::istream& input, data_struct_t& data)
{
  StreamGuard guard(input);
  input >> std::noskipws;
  std::istream::sentry sentry(input);
  if (sentry)
  {
    int key1;
    char symbol;
    if (!(input >> skipSpaces >> key1 >> skipSpaces >> symbol))
    {
      return input;
    }
    if (symbol != COMMA)
    {
      input.setstate(std::ios::failbit);
      return input;
    }
    int key2;
    if (!(input >> skipSpaces >> key2 >> skipSpaces >> symbol))
    {
      return input;
    }

    if (symbol != COMMA)
    {
      input.setstate(std::ios::failbit);
      return input;
    }
    std::string inputString;
    std::getline(input >> skipSpaces, inputString);
    if (!input.eof() && input.fail())
    {
      return input;
    }
    if ((std::abs(key1) > MAX_NUMBER) || (std::abs(key2) > MAX_NUMBER))
    {
      input.setstate(std::ios::failbit);
      return input;
    }
    data.key1 = key1;
    data.key2 = key2;
    data.str = inputString;
  }
  return input;

}

bool operator< (const data_struct_t& data1, const data_struct_t& data2)
{
  if ((data1.key1 == data2.key1) && (data1.key2 == data2.key2))
  {
    return (data1.str.length() < data2.str.length());
  }
  else if (data1.key1 == data2.key1)
  {
    return (data1.key2 < data2.key2);
  }
  else
  {
    return (data1.key1 < data2.key1);
  }
}
