#include "parser.hpp"
#include <istream>
#include <sstream>
#include <unordered_map>
#include <functional>

CommandType parseAdd(std::stringstream& sstream)
{
  std::string data, priority;
  sstream >> priority;
  if (sstream.fail())
  {
    return &printError;
  }
  QueueWithPriority<std::string>::ElementPriority priorElem;
  if (priority == "high")
  {
    priorElem = QueueWithPriority<std::string>::ElementPriority::HIGH;
  }
  else if (priority == "normal")
  {
    priorElem = QueueWithPriority<std::string>::ElementPriority::NORMAL;
  }
  else if (priority == "low")
  {
    priorElem = QueueWithPriority<std::string>::ElementPriority::LOW;
  }
  else
  {
    return &printError;
  }
  std::getline(sstream >> std::ws, data);
  if (data.empty())
  {
    return std::bind(&printError, std::placeholders::_1);
  }
  else
  {
    return std::bind(&add, std::placeholders::_1, priorElem, data);
  }
}

CommandType parseGet(std::stringstream& sstream)
{
  std::string nextWord;
  sstream >> nextWord;
  if (!nextWord.empty())
  {
    return &printError;
  }
  return &get;
}

CommandType parseAccelerate(std::stringstream& sstream)
{
  std::string nextWord;
  sstream >> nextWord;
  if (!nextWord.empty())
  {
    return std::bind(&printError, std::placeholders::_1);
  }
  return std::bind(&accelerate, std::placeholders::_1);
}

using ParsingTypeMap = std::unordered_map<std::string, CommandType(*)(std::stringstream&)>;
const ParsingTypeMap parsingMap
  {
    {"add", &parseAdd},
    {"get", &parseGet},
    {"accelerate", &parseAccelerate}
  };

CommandType parse(std::string& fullCommand)
{
  std::stringstream stream(fullCommand);
  std::string command;
  stream >> command;
  if (command.empty())
  {
    return std::bind(&printError, std::placeholders::_1);
  }
  auto iter = parsingMap.find(command);
  if (iter == parsingMap.end())
  {
    return std::bind(&printError, std::placeholders::_1);
  }
  else
  {
    return iter->second(stream);
  }
}
