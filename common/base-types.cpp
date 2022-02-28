#include "base-types.hpp"

bool gorshechnikov::isIntersect(const rectangle_t &rect1, const rectangle_t &rect2) {
  bool temp1 = fabs(rect2.pos.x - rect1.pos.x) < ((rect2.width / 2) + (rect1.width / 2));
  bool temp2 = fabs(rect2.pos.y - rect1.pos.y) < ((rect2.height / 2) + (rect1.height / 2));
  return temp1 && temp2;
}

