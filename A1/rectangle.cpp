#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
  rec_{ width, height, pos }
{
  assert((width > 0.0) && (height > 0.0));
}

double Rectangle::getHeight() const
{
  return rec_.height;
}

double Rectangle::getWidth() const
{
  return rec_.width;
}

point_t Rectangle::getCenter() const
{
  return rec_.pos;
}

void Rectangle::print() const
{
  std::cout << "Created rectangle width: " << rec_.width << " height: "
      << rec_.height << " center: (" << rec_.pos.x << " ; " << rec_.pos.y
      << " )" << '\n';
}

double Rectangle::getArea() const
{
  return rec_.width * rec_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rec_;
}

void Rectangle::move(const point_t& pos)
{
  rec_.pos = pos;
}

void Rectangle::move(const double x, const double y)
{
  rec_.pos.x += x;
  rec_.pos.y += y;
}
