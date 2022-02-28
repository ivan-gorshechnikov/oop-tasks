
#ifndef A4_MATRIX_HPP
#define A4_MATRIX_HPP
#include <memory>
#include "shape.hpp"

namespace gorshechnikov
{
  class Matrix {
  public:
    class Layer {
    public:
      Shape::SharedPtr operator[] (size_t index);
      const Shape::SharedPtr operator[](size_t index) const;
    private:
      friend class Matrix;
      Shape::SharedPtr *layer_;
      size_t size_;
      Layer(Shape::SharedPtr* layer, size_t size);
    };
    Matrix();
    Matrix(Matrix &other);
    Matrix(Matrix &&other) noexcept ;
    ~Matrix() = default;
    Matrix& operator=(Matrix &other);
    Matrix& operator=(Matrix &&other);
    Layer operator[](size_t index);
    const Layer operator[](size_t index) const;
    size_t getCountOfLayers() const noexcept;
    size_t getCountOfShapes() const noexcept;
    void add(const Shape::SharedPtr &shape);
    void print() const;
  private:
    size_t countOfShapes_;
    size_t countOfLayers_;
    std::unique_ptr<Shape::SharedPtr []> matrix_;
    size_t getNuLayerToAdd(const Shape::SharedPtr &shape);
    void moveOneMatrixIntoAnother(const std::unique_ptr<Shape::SharedPtr []>& matrix,
        bool isChangeNuShapes, bool isChangeNuLayers);
    size_t findPlaceInLayer(size_t shapeRow, bool &isChangeNuLayers, bool &isChangeNuShapes);
  };
}

#endif //A4_MATRIX_HPP
