#ifndef B1_SORT_HPP
#define B1_SORT_HPP
#include <stdexcept>
#include <functional>
#include "tasks.hpp"


template<template<class> class Access, class T>
void sort(T &container, SortingOrientation compare)
{
  typename Access<T>::iterator i = Access<T>::begin(container);
  typename Access<T>::iterator end = Access<T>::end(container);
  while (i != end)
  {
    typename Access<T>::iterator j = i;
    while (j != end)
    {
      typename T::value_type &left = Access<T>::getElement(container, j);
      typename T::value_type &right = Access<T>::getElement(container, i);
        switch (compare) {
          case ASCENDING:
            if (left < right)
            {
              std::swap(left, right);
            }
            break;
          case DESCENDING:
            if (left > right)
            {
              std::swap(left, right);
            }
            break;
      }
      j++;
    }
    i++;
  }
}

#endif
