#ifndef SHAPE_HPP
#define SHAPE_HPP
class Shape {
public:
  virtual ~Shape() = default;
  virtual struct point_t getCenter() const = 0;
  virtual double getArea() const = 0;
  virtual struct rectangle_t getFrameRect() const = 0;
  virtual void move(const struct point_t& pos_) = 0;
  virtual void move(const double x, const double y) = 0;
  virtual void print() const = 0;
};
#endif
