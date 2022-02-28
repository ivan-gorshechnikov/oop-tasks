#include "composite-shape.hpp"
#include <iostream>
#include <algorithm>
#include <math.h>


double gorshechnikov::CompositeShape::getArea() const
{
  if (!array_) {
    throw std::invalid_argument("ERROR: array is nullptr");
  }
  double sumArea = 0.0;
  for (size_t i = 0; i < size_; i++) {
    sumArea += array_[i]->getArea();
  }
  return sumArea;
}

gorshechnikov::CompositeShape::SharedPtr gorshechnikov::CompositeShape::operator[](size_t index)
{
  if (!array_) {
    throw std::invalid_argument("ERROR: array is nullptr");
  }
  if (index >= size_) {
    throw std::out_of_range("ERROR: Wrong index, more than size\n");
  }
  return array_[index];
}

const gorshechnikov::CompositeShape::SharedPtr gorshechnikov::CompositeShape::operator[](size_t index) const
{
  if (!array_) {
    throw std::invalid_argument("ERROR: array is nullptr");
  }
  if (index >= size_) {
    throw std::out_of_range("ERROR: Wrong index, more than size\n");
  }
  return array_[index];
}

void gorshechnikov::CompositeShape::addElement(const SharedPtr &figure)
{
  if (!figure) {
    throw std::invalid_argument("ERROR: No any figure\n");
  }
  std::unique_ptr<SharedPtr[]> tempArray = std::make_unique<SharedPtr[]>(size_ + 1);
  for (size_t i = 0; i < size_; i++) {
    tempArray[i] = array_[i];
  }
  tempArray[size_] = figure;
  size_++;
  array_.swap(tempArray);
}

gorshechnikov::rectangle_t gorshechnikov::CompositeShape::getFrameRect() const
{
  if (!array_) {
    throw std::invalid_argument("ERROR: Array is nullptr");
  }
  rectangle_t frameRect{array_[0]->getFrameRect()};
  double maxLeft = frameRect.pos.x - frameRect.width / 2;
  double maxRight = frameRect.pos.x + frameRect.width / 2;
  double maxDown = frameRect.pos.y - frameRect.height / 2;
  double maxUp = frameRect.pos.y + frameRect.height / 2;
  for (size_t i = 1; i < size_; i++) {
    frameRect = array_[i]->getFrameRect();
    maxLeft = std::min(maxLeft, frameRect.pos.x - frameRect.width / 2);
    maxRight = std::max(maxRight, frameRect.pos.x + frameRect.width / 2);
    maxDown = std::min(maxDown, frameRect.pos.y - frameRect.height / 2);
    maxUp = std::max(maxUp, frameRect.pos.y + frameRect.height / 2);
  }
  double width = maxRight - maxLeft;
  double height = maxUp - maxDown;
  return rectangle_t{width, height, {(maxLeft + maxRight) / 2, (maxDown + maxUp) / 2}};
}

void gorshechnikov::CompositeShape::move(const gorshechnikov::point_t &pos)
{
  point_t tempPoint = getFrameRect().pos;
  move(pos.x - tempPoint.x, pos.y - tempPoint.y);

}

void gorshechnikov::CompositeShape::print() const
{
  std::cout << "Composite shape\n";
  for (size_t i = 0; i < size_; i++) {
    std::cout << i + 1 << " figure:\n";
    this->array_[i]->print();
  }
}

void gorshechnikov::CompositeShape::move(double x, double y)
{
  for (size_t i = 0; i < size_; i++) {
    this->array_[i]->move(x, y);
  }
}

void gorshechnikov::CompositeShape::scale(double coefficient)
{
  if (coefficient < 0.0) {
    throw std::invalid_argument("ERROR: Negative coefficient\n");
  }
  point_t centreFrameRect = getCentre();
  for (size_t i = 0; i < size_; i++) {
    double posX = (array_[i]->getCentre().x - centreFrameRect.x) * coefficient + centreFrameRect.x;
    double posY = (array_[i]->getCentre().y - centreFrameRect.y) * coefficient + centreFrameRect.y;
    array_[i]->move({posX, posY});
    this->array_[i]->scale(coefficient);
  }
}

gorshechnikov::CompositeShape::CompositeShape(const SharedPtr &shape) :
  array_(std::make_unique<SharedPtr[]>(1)),
  size_(1)
{
  if (!shape) {
    throw std::invalid_argument("ERROR: Shape is not exist\n");
  }
  array_[0] = shape;
}

gorshechnikov::CompositeShape::CompositeShape(const gorshechnikov::CompositeShape &otherCompositeShape) :
  array_(std::make_unique<SharedPtr[]>(otherCompositeShape.size_)),
  size_(otherCompositeShape.size_)
{
  for (size_t i = 0; i < otherCompositeShape.size_; i++) {
    array_[i] = otherCompositeShape.array_[i];
  }
}

gorshechnikov::CompositeShape &
    gorshechnikov::CompositeShape::operator=(const gorshechnikov::CompositeShape &otherCompositeShape)
{
  if (this == &otherCompositeShape) {
    return *this;
  }

  this->size_ = otherCompositeShape.size_;
  this->array_ = std::make_unique<SharedPtr[]>(otherCompositeShape.size_);
  for (size_t i = 0; i < otherCompositeShape.size_; i++) {
    array_[i] = otherCompositeShape.array_[i];
  }
  return *this;
}

size_t gorshechnikov::CompositeShape::getSize() const
{
  return this->size_;
}

void gorshechnikov::CompositeShape::popIndex(size_t index)
{
  if (index >= size_) {
    throw std::invalid_argument("ERROR: This argument is invalid: " + std::to_string(index) + "\n");
  }
  if (size_ < 2) {
    throw std::invalid_argument("ERROR: Can't delete last shape of composite shapes_\n");
  }
  std::unique_ptr<SharedPtr[]> tempArray = std::make_unique<SharedPtr[]>(size_ - 1);

  for (size_t i = 0, j = 0; i < size_; i++) {
    if (index != i) {
      tempArray[j] = array_[i];
      j++;
    }
  }
  std::swap(tempArray, array_);
  --size_;
}

gorshechnikov::point_t gorshechnikov::CompositeShape::getCentre() const
{
  return getFrameRect().pos;
}

void gorshechnikov::CompositeShape::rotate(double angle) {
  const double a = angle / 180 * M_PI;
  const double sinAngle = sin(a);
  const double cosAngle = cos(a);
  const point_t frameRectCentre = getCentre();
  for (size_t i = 0; i < size_; i++)
  {
    const point_t shapeCentre = array_[i]->getCentre();
    double posX = (shapeCentre.x - frameRectCentre.x) * cosAngle - (shapeCentre.y - frameRectCentre.y) * sinAngle + frameRectCentre.x;
    double posY = (shapeCentre.x - frameRectCentre.x) * sinAngle + (shapeCentre.y - frameRectCentre.y) * cosAngle + frameRectCentre.y;
    array_[i]->move({posX, posY});
    array_[i]->rotate(angle);
  }
}
