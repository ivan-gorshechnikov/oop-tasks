#include <cmath>
#include <iostream>
#include "matrix.hpp"
#include "base-types.hpp"


gorshechnikov::Matrix::Layer::Layer(gorshechnikov::Shape::SharedPtr *layer, size_t size):
  layer_(layer),
  size_(size)
{}

gorshechnikov::Shape::SharedPtr gorshechnikov::Matrix::Layer::operator[](size_t index) {
  if (index >= size_) {
    throw std::out_of_range("ERROR: Out of range\n");
  }
  return layer_[index];
}

const gorshechnikov::Shape::SharedPtr gorshechnikov::Matrix::Layer::operator[](size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("ERROR: Out of range\n");
  }
  return layer_[index];
}

gorshechnikov::Matrix::Matrix() :
  countOfShapes_(0),
  countOfLayers_(0),
  matrix_(nullptr)
{}

gorshechnikov::Matrix::Matrix(gorshechnikov::Matrix &other) :
  countOfShapes_(other.countOfShapes_),
  countOfLayers_(other.countOfLayers_),
  matrix_(std::make_unique<Shape::SharedPtr[]>(countOfLayers_ * countOfLayers_))
{
  for (size_t i = 0; i < countOfLayers_ * countOfShapes_; i++)
  {
    matrix_[i] = other.matrix_[i];
  }
}

gorshechnikov::Matrix::Matrix(gorshechnikov::Matrix &&other) noexcept :
  countOfShapes_(other.countOfShapes_),
  countOfLayers_(other.countOfLayers_),
  matrix_(std::move(other.matrix_))
{
  other.countOfShapes_ = 0;
  other.countOfLayers_ = 0;
  other.matrix_.reset();
}

gorshechnikov::Matrix &gorshechnikov::Matrix::operator=(gorshechnikov::Matrix &other)
{
  if (this == &other)
  {
    return *this;
  }
  countOfShapes_ = other.countOfShapes_;
  countOfLayers_ = other.countOfLayers_;
  matrix_ = std::make_unique<Shape::SharedPtr[]>(countOfLayers_ * countOfShapes_);
  for (size_t i = 0; i < countOfLayers_ * countOfShapes_; i++)
  {
    matrix_[i] = other.matrix_[i];
  }
  return *this;
}

gorshechnikov::Matrix &gorshechnikov::Matrix::operator=(gorshechnikov::Matrix &&other)
{
  if (this == &other)
  {
    return *this;
  }
  countOfShapes_ = other.countOfShapes_;
  countOfLayers_ = other.countOfLayers_;
  matrix_ = std::move(other.matrix_);
  other.countOfShapes_ = 0;
  other.countOfLayers_ = 0;
  other.matrix_.reset();
  return *this;
}

void gorshechnikov::Matrix::add(const gorshechnikov::Shape::SharedPtr &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("ERROR: Adding shape is nullptr\n");
  }
  size_t shapeRow = getNuLayerToAdd(shape);
  bool isChangeNuShapes = false;
  bool isChangeNuLayers = false;
  size_t placeInLayer = findPlaceInLayer(shapeRow, isChangeNuLayers, isChangeNuShapes);
  std::unique_ptr<Shape::SharedPtr[]> tempMatrix = nullptr;
  if (isChangeNuLayers || isChangeNuShapes)
  {
    tempMatrix = std::make_unique<Shape::SharedPtr[]>(countOfShapes_ * countOfLayers_);
    moveOneMatrixIntoAnother(tempMatrix, isChangeNuShapes, isChangeNuLayers);
    tempMatrix[shapeRow * countOfShapes_ + placeInLayer] = shape;
    matrix_ = std::move(tempMatrix);
  }
  else
  {
    matrix_[shapeRow * countOfShapes_ + placeInLayer] = shape;
  }
}

void gorshechnikov::Matrix::print() const
{
  std::cout << "Matrix size = " << countOfShapes_ * countOfLayers_ << '\n'
            << getCountOfLayers() << " layers and " << getCountOfShapes() << " shapes:\n";
  for (size_t i = 0; i < countOfLayers_; i++)
  {
    for (size_t j = 0; j < countOfShapes_; j++)
    {
      if (matrix_[i * countOfShapes_ + j] != nullptr)
      {
        std::cout << i + 1 << '.' << j + 1 << '\n';
        matrix_[i * countOfShapes_ + j]->print();
      }
    }
  }
}

size_t gorshechnikov::Matrix::getCountOfLayers() const noexcept
{
  return countOfLayers_;
}

size_t gorshechnikov::Matrix::getCountOfShapes() const noexcept
{
  return countOfShapes_;
}

gorshechnikov::Matrix::Layer gorshechnikov::Matrix::operator[](size_t index)
{
  if (index >= countOfLayers_)
  {
    throw std::out_of_range("ERROR: More than shapes in layer\n");
  }
  Layer layer(&matrix_[countOfLayers_ * index], countOfShapes_);
  return layer;
}

const gorshechnikov::Matrix::Layer gorshechnikov::Matrix::operator[](size_t index) const
{
  if (index >= countOfLayers_)
  {
    throw std::out_of_range("ERROR: More than shapes in layer\n");
  }
  Layer layer(&matrix_[countOfLayers_ * index], countOfShapes_);
  return layer;
}

size_t gorshechnikov::Matrix::getNuLayerToAdd(const gorshechnikov::Shape::SharedPtr &shape)
{
  size_t shapeRow = 0;
  gorshechnikov::rectangle_t tempRectShape = shape->getFrameRect();
  for (size_t i = 0; i < countOfLayers_ * countOfShapes_; i++)
  {
    if (isIntersect(tempRectShape, matrix_[i]->getFrameRect()))
    {
      shapeRow = i / countOfShapes_ + 1;
    }
  }
  return shapeRow;
}

void gorshechnikov::Matrix::moveOneMatrixIntoAnother(const std::unique_ptr<Shape::SharedPtr []> &matrix,
    bool isChangeNuShapes, bool isChangeNuLayers)
{
  size_t oldCountOfShapes = isChangeNuShapes ? countOfShapes_ - 1 : countOfShapes_;
  size_t oldCountOfLayers = isChangeNuLayers ? countOfLayers_ - 1 : countOfLayers_;
  for (size_t i = 0; i < countOfLayers_; i++)
  {
    for (size_t j = 0; j < countOfShapes_; j++)
    {
      if ((i >= oldCountOfLayers) || (j >= oldCountOfShapes))
      {
        matrix[i * countOfShapes_ + j] = nullptr;
        continue;
      }
      matrix[i * countOfShapes_ + j] = matrix_[i * oldCountOfShapes + j];
    }
  }
}


size_t gorshechnikov::Matrix::findPlaceInLayer(size_t shapeRow, bool &isChangeNuLayers, bool &isChangeNuShapes) {
  size_t placeInLayer = countOfShapes_;
  if (shapeRow >= countOfLayers_)
  {
    countOfLayers_++;
    isChangeNuLayers = true;
    placeInLayer = 0;
  }
  else
  {
    for (size_t i = shapeRow * countOfShapes_; i < (shapeRow + 1) * countOfShapes_; i++)
    {
      if (matrix_[i] == nullptr)
      {
        placeInLayer = i - shapeRow * countOfShapes_ + 1;
        break;
      }
    }
  }
  if (placeInLayer == countOfShapes_)
  {
    countOfShapes_++;
    isChangeNuShapes = true;
    placeInLayer = countOfShapes_ - 1;
  }
  return placeInLayer;
}

