#include "phone-interface.hpp"
#include <string>
#include <iostream>
#include "phone-book.hpp"

const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
const std::string EMPTY = "<EMPTY>\n";

PhoneInterface::PhoneInterface() :
  phoneBook_(),
  bookMarks_({ {"current", phoneBook_.end()} })
{}

void PhoneInterface::add(const std::string &name, const std::string &number)
{
  phoneBook_.pushBack(name, number);
  if (phoneBook_.begin() == std::prev(phoneBook_.end()))
  {
    bookMarks_.begin()->second--;
  }
}

void PhoneInterface::store(const std::string &markName, const std::string &newMarkName, std::ostream &outputStream)
{
  auto iter = bookMarks_.find(markName);
  if (iter != bookMarks_.end())
  {
    bookMarks_.insert(std::make_pair(newMarkName, iter->second));
  }
  else
  {
    outputStream << INVALID_BOOKMARK;
  }
}

void PhoneInterface::insert(const std::string &markName, const std::string &name, const std::string &number,
    std::ostream &outputStream, PhoneBook::Direction direction)
{
  auto it = bookMarks_.find(markName);
  if (it == bookMarks_.end())
  {
    outputStream << INVALID_BOOKMARK;
  }
  else
  {
    phoneBook_.insert(it->second, name, number, direction);
    if (phoneBook_.begin() == std::prev(phoneBook_.end()))
    {
      bookMarks_.begin()->second--;
    }
  }
}


void PhoneInterface::deleteBookMark(const std::string &markName, std::ostream &outputStream)
{
  auto iter = bookMarks_.find(markName);
  if (iter == bookMarks_.end())
  {
    outputStream << INVALID_BOOKMARK;
  }
  for (auto &bookIter : bookMarks_)
  {
    if ((bookIter.second == iter->second) && (bookIter.first != markName))
    {
      if (bookIter.second != std::prev(phoneBook_.end()))
      {
        bookIter.second++;
      }
      else
      {
        bookIter.second--;
      }
    }
  }
  if (iter->second != std::prev(phoneBook_.end()))
  {
    bookMarks_[markName] = phoneBook_.deleteContact(iter->second);
  }
  else
  {
    bookMarks_[markName] = std::prev(phoneBook_.deleteContact(iter->second));
  }
}


void PhoneInterface::show(const std::string &markName, std::ostream &outputStream)
{
  auto iter = bookMarks_.find(markName);
  if (iter == bookMarks_.end())
  {
    outputStream << INVALID_BOOKMARK;
  }
  else if (iter->second == phoneBook_.end())
  {
    outputStream << EMPTY;
  }
  else
  {
    outputStream << iter->second->number << " " << iter->second->name << "\n";
  }
}

void PhoneInterface::moveBookMark(const std::string &markName, int steps, std::ostream &outputStream)
{
  auto iter = bookMarks_.find(markName);
  if (iter == bookMarks_.end())
  {
    outputStream << INVALID_BOOKMARK;
  }
  else
  {
    if (steps > 0)
    {
      int count = steps;
      while (count != 0)
      {
        if (iter->second != prev(phoneBook_.end()))
        {
          ++iter->second;
          --count;
        }
        else
        {
          iter->second = phoneBook_.begin();
          --count;
        }
      }
    }
    if (steps < 0)
    {
      int count = steps;
      while (count != 0)
      {
        if (iter->second != phoneBook_.begin())
        {
          --iter->second;
          ++count;
        }
        else
        {
          iter->second = prev(phoneBook_.end());
          ++count;
        }
      }
    }
  }
}

void PhoneInterface::moveBookMark(const std::string &markName, Place place, std::ostream &outputStream)
{
  auto iter = bookMarks_.find(markName);
  if (iter == bookMarks_.end())
  {
    outputStream << INVALID_BOOKMARK;
  }
  else
  {
    switch (place)
    {
      case FIRST:
        iter->second = phoneBook_.begin();
        break;
      case LAST:
        iter->second = std::prev(phoneBook_.end());
        break;
      default:
        throw std::invalid_argument("Unknown place to move");
    }
  }
}
