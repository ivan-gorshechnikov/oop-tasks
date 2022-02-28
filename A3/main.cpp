#include <iostream>
#include <memory>
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/composite-shape.hpp"

int main() {
  gorshechnikov::Shape *figure = nullptr;

  const double rectangleWidth = 2.567;
  const double rectangleHeight = 4.835;
  const double coefficient = 8.9;
  const gorshechnikov::point_t rectangleCentre{3.129, -9.072};
  std::cout << "Expected rectangle width: " << rectangleWidth << " height: " << rectangleHeight << " center: ("
      << rectangleCentre.x << " ; " << rectangleCentre.y << " )" << '\n';
  std::unique_ptr<gorshechnikov::CompositeShape> array = nullptr;
  std::shared_ptr<gorshechnikov::Rectangle> temp = std::make_shared<gorshechnikov::Rectangle>
      (rectangleWidth, rectangleHeight, rectangleCentre);
  std::shared_ptr<gorshechnikov::Rectangle> temp1 = std::make_shared<gorshechnikov::Rectangle>
      (124, 12424, gorshechnikov::point_t{22, -8});
  try {
    array = std::make_unique<gorshechnikov::CompositeShape>
        (std::make_shared<gorshechnikov::Rectangle>(21, 4, gorshechnikov::point_t{22, -8}));
    array->addElement(temp);
    array->addElement(temp1);
    figure = new gorshechnikov::Rectangle(rectangleWidth, rectangleHeight, rectangleCentre);
  }
  catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  figure->print();
  gorshechnikov::point_t point = {45.98, -36};
  array->move(450000, 345);
  array->print();
  try {
    array->scale(12);
  }
  catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  array->print();
  array->popIndex(0);
  array->print();
  figure->move(912.56, -1000.0);
  figure->print();
  figure->move(point);
  figure->print();
  std::cout << "Area of rectangle: " << figure->getArea() << '\n';
  try {
    figure->scale(coefficient);
  }
  catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << '\n';
    delete figure;
    return 1;
  }
  figure->print();

  const double circleRadius = 7.12;
  const gorshechnikov::point_t circleCentre{0.15, -21};
  std::cout << "Expected circle radius: " << circleRadius << " centre: ( "
      << circleCentre.x << " ; " << circleCentre.y << " )" << '\n';
  try {
    figure = new gorshechnikov::Circle(circleRadius, circleCentre);
  }
  catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  figure->print();
  figure->move(123, 16.43);
  figure->print();
  point = {90.8, 52.78};
  figure->move(point);
  std::cout << "Area of circle: " << figure->getArea() << '\n';
  try {
    figure->scale(coefficient);
  }
  catch (const std::invalid_argument &ex) {
    std::cerr << ex.what() << '\n';
    delete figure;
    return 1;
  }
  figure->print();

  return 0;
}
