#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "base-types.hpp"

namespace gorshechnikov {
  class CompositeShape : public Shape {
  public:
    CompositeShape(const CompositeShape &otherCompositeShape);

    CompositeShape(CompositeShape &&otherCompositeShape) = default;

    CompositeShape(const SharedPtr &shape);

    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &otherCompositeShape);

    CompositeShape &operator=(CompositeShape &&otherCompositeShape) = default;

    SharedPtr operator[](size_t index);

    const SharedPtr operator[](size_t index) const;

    void addElement(const SharedPtr &figure);

    void popIndex(size_t index);

    virtual double getArea() const override;

    size_t getSize() const;

    point_t getCentre() const override;

    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &pos) override;

    virtual void print() const override;

    virtual void move(double x, double y) override;

    virtual void rotate(double angle) override;

    virtual void scale(double coefficient) override;

  private:
    std::unique_ptr<SharedPtr[]> array_;
    size_t size_;
  };
}

#endif //A3_COMPOSITE_SHAPE_HPP
