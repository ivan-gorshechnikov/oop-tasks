#ifndef B3_COMMANDS_HPP
#define B3_COMMANDS_HPP

#include <istream>
#include <memory>
#include "phone-interface.hpp"

const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";
const std::string INVALID_STEP = "<INVALID STEP>\n";

struct QuotedName
{
  std::string& name;
};

std::istream& operator>>(std::istream& input, QuotedName contactName);

struct PhoneNumber
{
  std::string& number;
};

std::istream& operator>>(std::istream& input, PhoneNumber contactMarkName);

struct MarkName
{
  std::string& markName;
};

std::istream& operator>>(std::istream& input, MarkName contactMarkName);

void print(std::ostream &out, const std::string &str);

void add(PhoneInterface &phoneBook, const std::string &number, const std::string &name);
void store(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName, const std::string &newMarkName);
void insert(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName, const std::string &number,
    const std::string &name, PhoneBook::Direction direction);
void deleteMarkName(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName);
void showMarkName(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName);
void moveToPosition(PhoneInterface &phoneBook, std::ostream&, const std::string &markName, PhoneInterface::Place pos);
void moveToSteps(PhoneInterface &phoneBook, std::ostream&, const std::string &markName, int steps);

#endif //B3_COMMANDS_HPP
