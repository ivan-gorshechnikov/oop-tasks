#include "circle.hpp"

#include <cmath>
#include <iostream>

gorshechnikov::Circle::Circle(double radius, const point_t &center) :
  radius_(radius), centre_(center)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("ERROR: Radius can't be less than zero");
  }
}

double gorshechnikov::Circle::getRadius() const
{
  return radius_;
}

gorshechnikov::point_t gorshechnikov::Circle::getCentre() const
{
  return centre_;
}

double gorshechnikov::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

gorshechnikov::rectangle_t gorshechnikov::Circle::getFrameRect() const
{
  return rectangle_t{2.0 * radius_, 2.0 * radius_, {centre_}};
}

void gorshechnikov::Circle::move(const point_t &pos)
{
  centre_ = pos;
}

void gorshechnikov::Circle::print() const
{
  std::cout << "Created circle radius: " << radius_ << " centre: (" << centre_.x << " ; " << centre_.y << ")"
      << '\n';
}

void gorshechnikov::Circle::move(double x, double y)
{
  centre_.x += x;
  centre_.y += y;
}

void gorshechnikov::Circle::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("wrong coefficient");
  }
  radius_ *= coefficient;
}

void gorshechnikov::Circle::rotate(double)
{}
