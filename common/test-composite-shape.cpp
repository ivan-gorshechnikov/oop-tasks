#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <memory>
#include <cmath>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON = 0.000001;
const double RADIUS = 6.8;
const double WIDTH = 6.6;
const double HEIGHT = 4.4;
const gorshechnikov::point_t CENTRE = {4.6, -4.5};
const gorshechnikov::point_t CENTRE1 = {9.1, 67.8};
const gorshechnikov::point_t POINT = {-8.1, 3.2};
const double DX = 5.8;
const double DY = 12.56;
const double COEFFICIENT = 5.0;
const double INVALID_COEFFICIENT = -0.56;
const double ANGLE = 45;

BOOST_AUTO_TEST_SUITE(CompositeShapeConstructor)

  BOOST_AUTO_TEST_CASE(CompositeShapeConstructor_CircleAsParameter_NoExceptions)
  {
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    gorshechnikov::CompositeShape array(circle);
    const double frameWidth = circle->getFrameRect().width;
    const double frameHeight = circle->getFrameRect().height;
    BOOST_CHECK_EQUAL(array.getSize(), 1);
    BOOST_CHECK_CLOSE(array.getArea(), circle->getArea(), EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.x, CENTRE.x, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.y, CENTRE.y, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeConstructor_RectangleAsParameter_NoExceptions)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    gorshechnikov::CompositeShape array(rect);
    const double frameWidth = rect->getFrameRect().width;
    const double frameHeight = rect->getFrameRect().height;
    BOOST_CHECK_EQUAL(array.getSize(), 1);
    BOOST_CHECK_CLOSE(array.getArea(), rect->getArea(), EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.x, CENTRE.x, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.y, CENTRE.y, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeConstructor_NullptrAsParameter_ExceptionThrow)
  {
    BOOST_CHECK_THROW(gorshechnikov::CompositeShape(nullptr), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeAddElement)

  BOOST_AUTO_TEST_CASE(CompositeShapeAddElement_ValidArgument_NoException)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeAddElement_NullprAsParameter_ExceptionThrow)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    gorshechnikov::CompositeShape array(rect);
    BOOST_CHECK_THROW(array.addElement(nullptr), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeRemove)

  BOOST_AUTO_TEST_CASE(CompositeShapeRemove_ValidArgument_NoException)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    array.popIndex(1);
    BOOST_CHECK_EQUAL(array.getSize(), 1);
    BOOST_CHECK_EQUAL(array[0], circle);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemove_ParameterMoreOrEqualThenSize_ExceptionThrow)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    BOOST_CHECK_THROW(array.popIndex(array.getSize()), std::invalid_argument);
    BOOST_CHECK_THROW(array.popIndex(10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRemove_DeleteLastElement_ExceptionThrow)
  {
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    gorshechnikov::CompositeShape array(circle);
    BOOST_CHECK_THROW(array.popIndex(0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeMoving)

  BOOST_AUTO_TEST_CASE(CompositeShapeMovingInPoint_ValidArgument_NoExceptions)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    gorshechnikov::rectangle_t frame = array.getFrameRect();
    double area = array.getArea();
    array.move(POINT);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.x, POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.y, POINT.y, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_CLOSE(array.getArea(), area, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeMovingOnAxes_ValidArgument_NoExceptions)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    gorshechnikov::rectangle_t frame = array.getFrameRect();
    double area = array.getArea();

    array.move(DX, DY);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.x, frame.pos.x + DX, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.y, frame.pos.y + DY, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, frame.width, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, frame.height, EPSILON);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_CLOSE(array.getArea(), area, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeScalling)

  BOOST_AUTO_TEST_CASE(CompositeShapeScaling_PositiveCoefficient_NoExceptions)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    double area = array.getArea();
    gorshechnikov::point_t centre = array.getCentre();
    array.scale(COEFFICIENT);

    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
    BOOST_CHECK_CLOSE(centre.x, array.getCentre().x, EPSILON);
    BOOST_CHECK_CLOSE(centre.y, array.getCentre().y, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, 73, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, 406.5, EPSILON);
    BOOST_CHECK_EQUAL(array.getSize(), 2);
    BOOST_CHECK_CLOSE(array.getArea(), area * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getArea(), M_PI * RADIUS * RADIUS * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCentre().x, (CENTRE1.x - centre.x) * COEFFICIENT + centre.x, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCentre().y, (CENTRE1.y - centre.y) * COEFFICIENT + centre.y, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getArea(), WIDTH * HEIGHT * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCentre().x, (CENTRE.x - centre.x) * COEFFICIENT + centre.x, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCentre().y, (CENTRE.y - centre.y) * COEFFICIENT + centre.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeScaling_NegativeCoefficient_ExceptionThrow)
  {
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    BOOST_CHECK_THROW(array.scale(INVALID_COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeScaling_ZeroAsCoefficient_NoException)
  {
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    BOOST_CHECK_NO_THROW(array.scale(0.0));
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeScaling_OneAsCoefficient_NoException)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    gorshechnikov::rectangle_t rectangle = array.getFrameRect();
    BOOST_CHECK_NO_THROW(array.scale(1.0));
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.x, rectangle.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().pos.y, rectangle.pos.y, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, rectangle.width, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, rectangle.height, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeIndexing)

  BOOST_AUTO_TEST_CASE(CompositeShapeIndexing_ValidArgument_NoExceptions)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    BOOST_CHECK_EQUAL(array[0], circle);
    BOOST_CHECK_EQUAL(array[1], rect);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeIndexing_MoreThanSizeAsParameter_ExceptionThrow)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    BOOST_CHECK_THROW(array[array.getSize()], std::out_of_range);
    BOOST_CHECK_THROW(array[4], std::out_of_range);
    BOOST_CHECK_THROW(array[15], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeRotate)

BOOST_AUTO_TEST_CASE(CompositeShapeRotate_ValidArgument_NoException)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    double area = array.getArea();
    BOOST_CHECK_NO_THROW(array.rotate(ANGLE));
    BOOST_CHECK_CLOSE(array.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCentre().x, -14.9820111, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCentre().y, 58.2391179, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCentre().x, 32.9598286, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCentre().y, 3.9333171, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CompositeShapeRotate_ZeroAsParameter_NoException)
  {
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    gorshechnikov::CompositeShape array(circle);
    array.addElement(rect);
    gorshechnikov::point_t centre = array.getCentre();
    double area = array.getArea();
    array.rotate(0);
    BOOST_CHECK_CLOSE(array.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCentre().x, CENTRE1.x, EPSILON);
    BOOST_CHECK_CLOSE(array[0]->getCentre().y, CENTRE1.y, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCentre().x, CENTRE.x, EPSILON);
    BOOST_CHECK_CLOSE(array[1]->getCentre().y, CENTRE.y, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().width, 14.6, EPSILON);
    BOOST_CHECK_CLOSE(array.getFrameRect().height, 81.3, EPSILON);
    BOOST_CHECK_CLOSE(array.getCentre().x, centre.x, EPSILON);
    BOOST_CHECK_CLOSE(array.getCentre().y, centre.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
