#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main() {
  const double rectangleWidth = 2.567;
  const double rectangleHeight = 4.835;
  const point_t rectangleCentre = point_t{ 3.129, -9.072 };
  std::cout << "Expected rectange width: " << rectangleWidth << " height: " << rectangleHeight << " center: ("
      << rectangleCentre.x << " ; " << rectangleCentre.y << " )" << '\n';
  Rectangle rect = Rectangle{ rectangleWidth, rectangleHeight, rectangleCentre };
  rect.print();
  rect.move(912.56, -1000.0);
  rect.print();
  point_t point = { 45.98, -36 };
  rect.move(point);
  rect.print();

  const double circleRadius = 7.12;
  const point_t circleCentre = point_t{ 0.15 , -21 };
  std::cout << "Expected circle radius: " << circleRadius << " centre: ( "
      << circleCentre.x << " ; " << circleCentre.y << " )" << '\n';
  Circle circle = Circle{ circleRadius , circleCentre };
  circle.print();
  circle.move(123, 16.43);
  circle.print();
  point = { 90.8, 52.78 };
  circle.move(point);

  Shape* figure = &circle;
  std::cout << "Area of circle: " << figure->getArea() << '\n';
  figure = &rect;
  std::cout << "Area of rectangle: " << figure->getArea() << '\n';
  return 0;
}
