#ifndef B1_ACCESS_HPP
#define B1_ACCESS_HPP
#include <cstdlib>
template<typename T>
struct AccessByBrackets
{
  using elem = typename T::value_type;
  using iterator = typename T::size_type;
  static iterator begin(const T&)
  {
    return 0;
  }

  static iterator end(const T& container)
  {
    return container.size();
  }

  static elem& getElement(T& container, iterator index)
  {
    return container[index];
  }
};

template<typename T>
struct AccessByAt
{
  using elem = typename T::value_type;
  using iterator = typename T::size_type;
  static iterator begin(const T&)
  {
    return 0;
  }

  static iterator end(const T& container)
  {
    return container.size();
  }

  static elem& getElement(T& container, iterator index)
  {
    return container.at(index);
  }
};

template<class T>
struct AccessByIterator
{
  using elem = typename T::value_type;
  using iterator = typename T::iterator;

  static iterator begin(T& container)
  {
    return container.begin();
  }

  static iterator end(T& container)
  {
    return container.end();
  }

  static elem& getElement(T&, iterator it)
  {
    return (*it);
  }
};

#endif
