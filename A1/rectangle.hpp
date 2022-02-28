#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape {
public:
  Rectangle(const double width, const double height, const point_t& pos);

  double getHeight() const;

  double getWidth() const;

  virtual point_t getCenter() const override;

  virtual double getArea() const override;

  virtual rectangle_t getFrameRect() const override;

  virtual void move(const point_t& pos_) override;

  virtual void move(const double x, const double y) override;

  virtual void print() const override;
private:
  rectangle_t rec_;
};
#endif
