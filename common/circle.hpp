#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace gorshechnikov {
  class Circle : public Shape {
  public:
    Circle(double radius, const point_t &center);

    double getRadius() const;

    point_t getCentre() const override;

    virtual double getArea() const override;

    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &pos) override;

    virtual void print() const override;

    virtual void rotate(double angle) override;

    virtual void move(double x, double y) override;

    virtual void scale(double coefficient) override;

  private:
    double radius_;
    point_t centre_;
  };
}
#endif
