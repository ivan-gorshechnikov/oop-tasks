#include "commands.hpp"
#include <iostream>
#include "phone-interface.hpp"

void print(std::ostream &out, const std::string &str)
{
  out << str;
}

std::istream& operator>>(std::istream& input, QuotedName contactName)
{
  input >> std::ws;
  if (input.get() != '"')
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  input >> std::noskipws;
  char symbol;
  input >> symbol;
  while (input)
  {
    contactName.name.push_back(symbol);
    input >> symbol;
    if (symbol == '\"' && contactName.name.back() != '\\')
    {
      break;
    }
    if ((contactName.name.back() == '\\') && ((symbol == '"') || (symbol == '\\')))
    {
      contactName.name.pop_back();
    }
  }
  if (input.eof())
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  input >> std::ws;
  return input;
}

std::istream& operator>>(std::istream& input, PhoneNumber contactNumber)
{
  input >> contactNumber.number;

  if (contactNumber.number.empty())
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  for (auto &digit: contactNumber.number)
  {
    if (!std::isdigit(digit))
    {
      input.setstate(std::ios::failbit);
      return input;
    }
  }
  return input;
}

std::istream& operator>>(std::istream& input, MarkName contactMarkName)
{
  input >> contactMarkName.markName;

  if (contactMarkName.markName.empty())
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  for (auto &symbol: contactMarkName.markName)
  {
    if (!isalnum(symbol) && (symbol != '-'))
    {
      input.setstate(std::ios::failbit);
      return input;
    }
  }
  return input;
}

void add(PhoneInterface &phoneBook, const std::string &number, const std::string &name)
{
  phoneBook.add(name, number);
}

void store(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName, const std::string &newMarkName)
{
  phoneBook.store(markName, newMarkName, out);
}

void insert(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName, const std::string &number,
    const std::string &name, PhoneBook::Direction place)
{
  phoneBook.insert(markName, name, number, out, place);
}

void deleteMarkName(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName)
{
  phoneBook.deleteBookMark(markName, out);
}

void showMarkName(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName)
{
  phoneBook.show(markName, out);
}

void moveToPosition(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName, PhoneInterface::Place pos)
{
  phoneBook.moveBookMark(markName, pos, out);
}
void moveToSteps(PhoneInterface &phoneBook, std::ostream &out, const std::string &markName, int steps)
{
  phoneBook.moveBookMark(markName, steps, out);
}
