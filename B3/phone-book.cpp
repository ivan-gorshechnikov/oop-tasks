#include "phone-book.hpp"
#include <iostream>


PhoneBook::iterator PhoneBook::insert(iterator bookIterator, const std::string &name, const std::string &number, Direction direction)
{
  switch (direction)
  {
    case AFTER:
      if (phoneBook_.empty() || (bookIterator != phoneBook_.end()))
      {
        return phoneBook_.insert(++bookIterator, contact_t{name, number});
      }
      else
      {
        throw std::out_of_range("Iterator is out of range");
      }
      break;
    case BEFORE:
      return phoneBook_.insert(bookIterator, contact_t{name, number});
      break;
    default:
      throw std::invalid_argument("Unknown direction");
  }
}

void PhoneBook::pushBack(const std::string &name, const std::string &number)
{
  phoneBook_.push_back(contact_t{name, number});
}

PhoneBook::iterator PhoneBook::deleteContact(PhoneBook::iterator iterator)
{
  return phoneBook_.erase(iterator);
}

PhoneBook::iterator PhoneBook::begin()
{
  return phoneBook_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return phoneBook_.end();
}

PhoneBook::const_iterator PhoneBook::cbegin() const
{
  return phoneBook_.cbegin();
}

PhoneBook::const_iterator PhoneBook::cend() const
{
  return phoneBook_.cend();
}

