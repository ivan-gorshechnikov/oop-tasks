#ifndef B3_PARSER_HPP
#define B3_PARSER_HPP

#include <string>
#include <functional>
#include <ostream>
#include <unordered_map>
#include <memory>
#include "phone-interface.hpp"
#include "commands.hpp"

using CommandType = std::function<void(PhoneInterface &book, std::ostream &outStream)>;
using ParsingTypeMap = std::unordered_map<std::string, CommandType(*)(std::istringstream &)>;

struct QuotedCommandType
{
  CommandType commandType;
};

std::istream& operator>>(std::istream& input, QuotedCommandType &command);

#endif //B3_PARSER_HPP
