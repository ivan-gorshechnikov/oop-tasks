#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

#include <cmath>

namespace gorshechnikov
{
  struct point_t {
    double x;
    double y;
  };


  struct rectangle_t {
    double width;
    double height;
    point_t pos;
  };

  bool isIntersect(const rectangle_t &rect1, const rectangle_t &rect2);
}

#endif
