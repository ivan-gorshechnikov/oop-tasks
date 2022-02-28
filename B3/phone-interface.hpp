#ifndef B3_PHONE_INTERFACE_HPP
#define B3_PHONE_INTERFACE_HPP

#include <map>
#include "phone-book.hpp"

class PhoneInterface
{
public:
  enum Place
  {
    FIRST,
    LAST
  };
  PhoneInterface();
  void add(const std::string &name, const std::string &number);
  void store(const std::string &markName, const std::string &newMarkName, std::ostream &outputStream);
  void insert(const std::string &markName, const std::string &name, const std::string &number,
      std::ostream &outputStream, PhoneBook::Direction direction);
  void deleteBookMark(const std::string &markName, std::ostream &outputStream);
  void show(const std::string &markName, std::ostream &outputStream);
  void moveBookMark(const std::string &markName, int steps, std::ostream &outputStream);
  void moveBookMark(const std::string &markName, Place, std::ostream &outputStream);
private:
  PhoneBook phoneBook_;
  std::map<std::string, PhoneBook::iterator> bookMarks_;
};
#endif //B3_PHONE_INTERFACE_HPP
