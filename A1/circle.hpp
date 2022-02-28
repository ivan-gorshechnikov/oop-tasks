#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape {
public:
  Circle(const double radius, const point_t& center);

  double getRadius() const;

  virtual point_t getCenter() const override;

  virtual double getArea() const override;

  virtual rectangle_t getFrameRect() const override;

  virtual void move(const point_t& pos) override;

  virtual void print() const override;

  virtual void move(const double x, const double y) override;

private:
  double radius_;
  point_t centre_;
};
#endif
