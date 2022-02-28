#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace gorshechnikov {
  class Rectangle : public Shape {
  public:
    Rectangle(double width, double height, const point_t &pos, double angle = 0);

    double getHeight() const;

    double getWidth() const;

    point_t getCentre() const override;

    virtual double getArea() const override;

    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &pos_) override;

    virtual void move(double x, double y) override;

    virtual void rotate(double) override;

    virtual void print() const override;

    virtual void scale(double coefficient) override;

  private:
    point_t vertex_[4];
  };
}

#endif
