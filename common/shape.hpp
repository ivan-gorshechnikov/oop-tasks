#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>

namespace gorshechnikov {
  struct point_t;
  struct rectangle_t;

  class Shape {
  public:
    using SharedPtr = std::shared_ptr<Shape>;

    virtual ~Shape() = default;

    virtual point_t getCentre() const = 0;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &pos_) = 0;

    virtual void move(double x, double y) = 0;

    virtual void rotate(double) = 0;

    virtual void print() const = 0;

    virtual void scale(double coefficient) = 0;
  };
}

#endif
