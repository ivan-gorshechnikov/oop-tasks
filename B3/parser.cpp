#include <sstream>
#include "parser.hpp"
#include "commands.hpp"

CommandType parseAdd(std::istringstream &sin)
{
  std::string name, number;
  if (!(sin >> PhoneNumber{number} >> QuotedName{name}))
  {
    return std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
  }
  return std::bind(&add, std::placeholders::_1, number, name);
}

CommandType parseStore(std::istringstream &sin)
{
  std::string markName, newMarkName;
  if (!(sin >> MarkName{markName} >> MarkName{newMarkName}))
  {
    return std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
  }
  return std::bind(&store, std::placeholders::_1, std::placeholders::_2, markName, newMarkName);
}

CommandType parseInsert(std::istringstream &sin)
{
  std::string direction;
  sin >> direction;
  std::string markName, number, name;
  if (!(sin >> MarkName{markName} >> PhoneNumber{number} >> QuotedName{name}))
  {
    return std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
  }
  if (direction == "before")
  {
    return std::bind(&insert, std::placeholders::_1, std::placeholders::_2, markName, number, name, PhoneBook::BEFORE);
  }
  else if (direction == "after")
  {
    return std::bind(&insert, std::placeholders::_1, std::placeholders::_2, markName, number, name, PhoneBook::AFTER);
  }
  else
  {
    return std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
  }
}

CommandType parseDelete(std::istringstream &sin)
{
  std::string markName;
  if (!(sin >> MarkName{markName}))
  {
    return std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
  }
  return std::bind(&deleteMarkName, std::placeholders::_1, std::placeholders::_2, markName);
}

CommandType parseShow(std::istringstream &sin)
{
  std::string markName;
  if (!(sin >> MarkName{markName}))
  {
    return std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
  }
  return std::bind(&showMarkName, std::placeholders::_1, std::placeholders::_2, markName);
}

CommandType parseMove(std::istringstream &sin)
{
  std::string markName;
  std::string stringSteps;
  if (!(sin >> MarkName{markName} >> stringSteps))
  {
    return std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
  }
  if (stringSteps == "first")
  {
    return std::bind(&moveToPosition, std::placeholders::_1, std::placeholders::_2, markName, PhoneInterface::FIRST);
  }
  else if (stringSteps == "last")
  {
    return std::bind(&moveToPosition, std::placeholders::_1, std::placeholders::_2, markName, PhoneInterface::LAST);
  }
  else
  {
    int intSteps;
    try
    {
      size_t pos = 0;
      intSteps = std::stoi(stringSteps.data(), &pos, 10);
      if (pos != stringSteps.length())
      {
        return std::bind(&print, std::placeholders::_2, INVALID_STEP);
      }
    }
    catch (const std::exception &exep)
    {
      return std::bind(&print, std::placeholders::_2, INVALID_STEP);
    }
    return std::bind(&moveToSteps, std::placeholders::_1, std::placeholders::_2, markName, intSteps);
  }
}

const static ParsingTypeMap parsingMap
  {
    {"add",    &parseAdd},
    {"store",  &parseStore},
    {"insert", &parseInsert},
    {"delete", &parseDelete},
    {"show",   &parseShow},
    {"move",   &parseMove}
  };

std::istream &operator>>(std::istream &input, QuotedCommandType &commandType)
{
  std::string fullCommand;
  std::getline(input, fullCommand);
  std::istringstream stream(fullCommand);
  std::string command;
  stream >> command;
  if (command.empty())
  {
    commandType.commandType = std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
    return input;
  }
  auto iter = parsingMap.find(command);
  if (iter == parsingMap.end())
  {
    commandType.commandType = std::bind(&print, std::placeholders::_2, INVALID_COMMAND);
    return input;
  }
  else
  {
    commandType.commandType = iter->second(stream);
    return input;
  }
}
