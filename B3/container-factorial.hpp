#ifndef B3_CONTAINER_FACTORIAL_HPP
#define B3_CONTAINER_FACTORIAL_HPP

#include <iterator>

class ContainerFactorial
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t, std::ptrdiff_t, size_t*, size_t>
  {
  public:
    static const size_t MIN_ORDER = 1;

    static const size_t MAX_ORDER = 11;

    Iterator();

    Iterator(size_t order);

    reference operator*() const noexcept;

    Iterator &operator++();

    Iterator operator++(int);

    Iterator &operator--();

    Iterator operator--(int);

    bool operator==(const Iterator &rhs) const;

    bool operator!=(const Iterator &rhs) const;

  private:
    size_t order_;
    unsigned int value_;

    unsigned int getFactorial(size_t index) const;
  };
  using reverse_iterator = std::reverse_iterator<Iterator>;

  ContainerFactorial() = default;

  Iterator begin() const;
  Iterator end() const;
  reverse_iterator rbegin() const;
  reverse_iterator rend() const;
};


#endif //B3_CONTAINER_FACTORIAL_HPP
