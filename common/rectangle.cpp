#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include <math.h>

gorshechnikov::Rectangle::Rectangle(double width, double height, const point_t &pos, double angle) :
  vertex_{ {pos.x - width / 2.0, pos.y - height / 2.0}, {pos.x + width / 2.0, pos.y - height / 2.0},
      {pos.x + width / 2.0, pos.y + height / 2.0}, {pos.x - width / 2.0, pos.y + height / 2.0}}
{
  if (width < 0.0)
  {
    throw std::invalid_argument("ERROR: Rectangle's width can't be less then zero");
  }
  if (height < 0.0)
  {
    throw std::invalid_argument("ERROR: Rectangle's height can't be less then zero");
  }
  rotate(angle);
}

double gorshechnikov::Rectangle::getHeight() const
{
  return sqrt((vertex_[3].y - vertex_[0].y) * (vertex_[3].y - vertex_[0].y)
      + (vertex_[3].x - vertex_[0].x) * (vertex_[3].x - vertex_[0].x));
}
double gorshechnikov::Rectangle::getWidth() const
{
  return sqrt((vertex_[1].x - vertex_[0].x) * (vertex_[1].x - vertex_[0].x)
      + (vertex_[1].y - vertex_[0].y) * (vertex_[1].y - vertex_[0].y));
}

gorshechnikov::point_t gorshechnikov::Rectangle::getCentre() const
{
  return {(vertex_[0].x + vertex_[2].x) / 2, (vertex_[0].y + vertex_[2].y) / 2};
}

void gorshechnikov::Rectangle::print() const
{
  gorshechnikov::point_t centre = getCentre();
  std::cout << "Rectangle width: " << getWidth() << " height: "
      << getHeight() << " centre: (" << centre.x << " ; " << centre.y << ")" << " vertex coordinates:";
  for(size_t i = 0; i < 4; i++)
  {
    std::cout << " (" << vertex_[i].x << ", " << vertex_[i].y << ")";
  }
  std::cout << "\n";
}

double gorshechnikov::Rectangle::getArea() const
{
  return getWidth() * getHeight();
}

gorshechnikov::rectangle_t gorshechnikov::Rectangle::getFrameRect() const
{
  double maxLeft = vertex_[0].x;
  double maxRight = vertex_[0].x;
  double maxDown = vertex_[0].y;
  double maxUp = vertex_[0].y;
  for (size_t i = 1; i < 4; i++) {
    maxLeft = std::min(maxLeft, vertex_[i].x);
    maxRight = std::max(maxRight, vertex_[i].x);
    maxDown = std::min(maxDown, vertex_[i].y);
    maxUp = std::max(maxUp, vertex_[i].y);
  }
  double width = maxRight - maxLeft;
  double height = maxUp - maxDown;
  return rectangle_t{width, height, {(maxLeft + maxRight) / 2, (maxDown + maxUp) / 2}};
}

void gorshechnikov::Rectangle::move(const point_t &pos)
{
  gorshechnikov::point_t centre = getCentre();
  move(pos.x - centre.x, pos.y - centre.y);
}

void gorshechnikov::Rectangle::move(double x, double y)
{
  for(size_t i = 0; i < 4; i++)
  {
    vertex_[i].x += x;
    vertex_[i].y += y;
  }
}

void gorshechnikov::Rectangle::scale(double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("ERROR: Negative coefficient");
  }
  gorshechnikov::point_t centre = getCentre();
  for(size_t i = 0; i < 4; i++)
  {
    const double distanceX = (vertex_[i].x - centre.x) * coefficient;
    const double distanceY = (vertex_[i].y - centre.y) * coefficient;
    vertex_[i] = {centre.x + distanceX, centre.y + distanceY};
  }
}

void gorshechnikov::Rectangle::rotate(double angle)
{
  const double a = angle / 180 * M_PI;
  const double sinAngle = sin(a);
  const double cosAngle = cos(a);
  gorshechnikov::point_t centre = getCentre();
  for(size_t i = 0; i < 4; i++)
  {
    double posX = (vertex_[i].x - centre.x) * cosAngle - (vertex_[i].y - centre.y) * sinAngle + centre.x;
    double posY = (vertex_[i].x - centre.x) * sinAngle + (vertex_[i].y - centre.y) * cosAngle + centre.y;
    vertex_[i] = {posX, posY};
  }
}
