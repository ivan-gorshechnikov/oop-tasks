#include "container-factorial.hpp"

ContainerFactorial::Iterator ContainerFactorial::begin() const
{
  return Iterator::MIN_ORDER;
}

ContainerFactorial::Iterator ContainerFactorial::end() const
{
  return Iterator::MAX_ORDER;
}

ContainerFactorial::reverse_iterator ContainerFactorial::rbegin() const
{
  return std::make_reverse_iterator(begin());
}

ContainerFactorial::reverse_iterator ContainerFactorial::rend() const
{
  return std::make_reverse_iterator(end());
}

ContainerFactorial::Iterator::Iterator():
  order_(1),
  value_(1)
{}

ContainerFactorial::Iterator::Iterator(size_t order):
  order_(order),
  value_(getFactorial(order))
{
  if ((order < MIN_ORDER) || (order > MAX_ORDER))
  {
    throw std::out_of_range("Order is out of range!");
  }
}

ContainerFactorial::Iterator::reference ContainerFactorial::Iterator::operator*() const noexcept
{
  return value_;
}

ContainerFactorial::Iterator &ContainerFactorial::Iterator::operator++()
{
  ++order_;
  if (order_ > MAX_ORDER)
  {
    throw std::out_of_range("Order must be less than 11!");
  }
  value_ *= order_;
  return *this;
}

ContainerFactorial::Iterator ContainerFactorial::Iterator::operator++(int)
{
  const Iterator temp = *this;
  this->operator++();
  return temp;
}

ContainerFactorial::Iterator &ContainerFactorial::Iterator::operator--()
{
  if (order_ <= MIN_ORDER)
  {
    throw std::out_of_range("Order must be less than 11!");
  }
  value_ /= order_;
  --order_;
  return *this;
}

ContainerFactorial::Iterator ContainerFactorial::Iterator::operator--(int)
{
  const Iterator temp = *this;
  this->operator--();
  return temp;
}

bool ContainerFactorial::Iterator::operator==(const ContainerFactorial::Iterator &rhs) const
{
  return value_ == rhs.value_;
}

bool ContainerFactorial::Iterator::operator!=(const ContainerFactorial::Iterator &rhs) const
{
  return value_ != rhs.value_;
}

unsigned int ContainerFactorial::Iterator::getFactorial(size_t index) const
{
  size_t factorial = 1;
  for (size_t i = 1; i < index + 1; i++)
  {
    factorial *= i;
  }
  return factorial;
}
