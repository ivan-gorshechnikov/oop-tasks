#include <sstream>
#include <string>
#include <iostream>
#include <functional>
#include "queue.hpp"
#include "parser.hpp"

void printGet(std::string& element)
{
  std::cout << element << "\n";
};

void printError(QueueWithPriority<std::string>&)
{
  std::cout << "<INVALID COMMAND>\n";
}

void add(QueueWithPriority<std::string> &queue,
    QueueWithPriority<std::string>::ElementPriority priority, const std::string &str)
{
  if (str.empty())
  {
    printError(queue);
  }
  else
  {
    queue.put(str, priority);
  }
}
void get(QueueWithPriority<std::string> &queue)
{
  if (queue.isEmpty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    queue.get(std::bind(&printGet, std::placeholders::_1));
  }
}

void accelerate(QueueWithPriority<std::string> &queue)
{
  queue.accelerate();
}

void task1()
{
  std::string inputString;
  QueueWithPriority<std::string> queue;
  while (std::getline(std::cin, inputString))
  {
    if (inputString.empty())
    {
      continue;
    }
    CommandType command = parse(inputString);
    command(queue);
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Error while reading from stream");
  }
}
