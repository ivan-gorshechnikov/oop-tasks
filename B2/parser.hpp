#ifndef B2_PARSER_HPP
#define B2_PARSER_HPP
#include <functional>
#include <ostream>
#include "queue.hpp"
void add(QueueWithPriority<std::string> &queue,
    QueueWithPriority<std::string>::ElementPriority priority, const std::string &str);
void get(QueueWithPriority<std::string> &queue);
void accelerate(QueueWithPriority<std::string> &queue);
void printError(QueueWithPriority<std::string>&);
using CommandType = std::function<void(QueueWithPriority<std::string> & queue)>;
CommandType parse(std::string& fullCommand);

#endif
