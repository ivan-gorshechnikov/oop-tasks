#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cassert>

Circle::Circle(const double radius, const point_t & center) :
  radius_(radius), centre_(center)
{
  assert(radius > 0.0);
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getCenter() const
{
  return centre_;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ 2.0 * radius_, 2.0 * radius_, { centre_ } };
}

void Circle::move(const point_t& pos)
{
  centre_ = pos;
}

void Circle::print() const
{
  std::cout << "Created circle: radius " << radius_ << " centre ( " << centre_.x << " ; " << centre_.y << " )" << '\n';
}

void Circle::move(const double x, const double y)
{
  centre_.x += x;
  centre_.y += y;
}
