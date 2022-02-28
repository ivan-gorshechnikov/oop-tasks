#ifndef B3_PHONE_BOOK_HPP
#define B3_PHONE_BOOK_HPP
#include <list>
#include <string>
class PhoneBook
{
public:
  struct contact_t
  {
    std::string name;
    std::string number;
  };
  enum Direction
  {
    AFTER,
    BEFORE
  };
  using iterator = std::list<contact_t>::iterator;
  using const_iterator = std::list<contact_t>::const_iterator;

  iterator insert(iterator bookIterator, const std::string &name, const std::string &phoneNumber, Direction direction);
  void pushBack(const std::string &newName, const std::string &newPhone);
  iterator deleteContact(iterator iter);
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

private:
  std::list<contact_t> phoneBook_;
};
#endif //B3_PHONE_BOOK_HPP
