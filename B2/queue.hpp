#ifndef B2_QUEUE_HPP
#define B2_QUEUE_HPP

#include <list>
#include <stdexcept>
#include <functional>

template<typename T>
class QueueWithPriority
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void put(const T &element, ElementPriority priority);

  template <typename function>
  void get(const function&);

  void accelerate();

  bool isEmpty() const;

private:
  std::list<T> lowPriority_;
  std::list<T> normalPriority_;
  std::list<T> highPriority_;
};

template<typename T>
void QueueWithPriority<T>::put(const T &element, QueueWithPriority::ElementPriority priority)
{
  switch (priority)
  {
    case HIGH:
      highPriority_.push_back(element);
      break;
    case NORMAL:
      normalPriority_.push_back(element);
      break;
    case LOW:
      lowPriority_.push_back(element);;
      break;
    default:
      throw std::invalid_argument("Unknown priority");
  }
}

template<typename T>
template<typename function>
void QueueWithPriority<T>::get(const function& print)
{
  if (!highPriority_.empty())
  {
    print(highPriority_.front());
    highPriority_.pop_front();
  }
  else if (!normalPriority_.empty())
  {
    print(normalPriority_.front());
    normalPriority_.pop_front();
  }
  else if (!lowPriority_.empty())
  {
    print(lowPriority_.front());
    lowPriority_.pop_front();
  }
  else
  {
    throw std::logic_error("Queue underflow!");
  }
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const
{
  return lowPriority_.empty() && normalPriority_.empty() && highPriority_.empty();
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  if (!lowPriority_.empty())
  {
    highPriority_.splice(highPriority_.end(), lowPriority_);
  }
}

#endif
