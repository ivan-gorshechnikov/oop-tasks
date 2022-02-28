#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "base-types.hpp"
#include "rectangle.hpp"


const double EPSILON = 0.000001;
const double WIDTH = 6.6;
const double HEIGHT = 4.4;
const double INVALID_WIDTH = -10.3;
const double INVALID_HEIGHT = -65.9;
const double DX = 1.6;
const double DY = 2.8;
const gorshechnikov::point_t CENTER = {3.5, 2.0};
const gorshechnikov::point_t POINT = {1.6, 2.8};
const double COEFFICIENT = 1.5;
const double INVALID_COEFFICIENT = -6.7;
const double AREA = WIDTH * HEIGHT;
const double ANGLE = 45;

BOOST_AUTO_TEST_SUITE(RectangleConstruct)

  BOOST_AUTO_TEST_CASE(RectangleConstructor_ValidArguments_NoExceptions)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    const double width = rect.getWidth();
    const double height = rect.getHeight();
    const double area = rect.getArea();
    const double frameWidth = rect.getFrameRect().width;
    const double frameHeight = rect.getFrameRect().height;
    BOOST_CHECK_CLOSE(rect.getWidth(), width, EPSILON);
    BOOST_CHECK_CLOSE(rect.getHeight(), height, EPSILON);
    BOOST_CHECK_CLOSE(rect.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleConstructor_NegativeWidth_ExceptionThrow)
  {
    BOOST_CHECK_THROW(gorshechnikov::Rectangle(INVALID_WIDTH, HEIGHT, CENTER), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RectangleConstructor_NegativeHeight_ExceptionThrow)
  {
    BOOST_CHECK_THROW(gorshechnikov::Rectangle(WIDTH, INVALID_HEIGHT, CENTER), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RectangleConstructor_ZeroAsWidth_ExceptionThrow)
  {
    BOOST_CHECK_NO_THROW(gorshechnikov::Rectangle(0.0, HEIGHT, CENTER));
  }

  BOOST_AUTO_TEST_CASE(RectangleConstructor_ZeroAsHeight_ExceptionThrow)
  {
    BOOST_CHECK_NO_THROW(gorshechnikov::Rectangle(WIDTH, 0.0, CENTER));
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleMoving)

  BOOST_AUTO_TEST_CASE(RectangleMovingInPoint_ValidArgument_NoExceptions)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    const double width = rect.getWidth();
    const double height = rect.getHeight();
    const double area = rect.getArea();
    const double frameWidth = rect.getFrameRect().width;
    const double frameHeight = rect.getFrameRect().height;
    rect.move(POINT);
    BOOST_CHECK_CLOSE(rect.getWidth(), width, EPSILON);
    BOOST_CHECK_CLOSE(rect.getHeight(), height, EPSILON);
    BOOST_CHECK_CLOSE(rect.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().x, POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().y, POINT.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, POINT.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleMovingOnAxes_ValidArgument_NoExceptions)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    const double width = rect.getWidth();
    const double height = rect.getHeight();
    const double area = rect.getArea();
    const double x = rect.getCentre().x;
    const double y = rect.getCentre().y;
    const double posX = rect.getFrameRect().pos.x;
    const double posY = rect.getFrameRect().pos.y;
    const double frameWidth = rect.getFrameRect().width;
    const double frameHeight = rect.getFrameRect().height;
    rect.move(DX, DY);
    BOOST_CHECK_CLOSE(rect.getWidth(), width, EPSILON);
    BOOST_CHECK_CLOSE(rect.getHeight(), height, EPSILON);
    BOOST_CHECK_CLOSE(rect.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().x, x + DX, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().y, y + DY, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, posX + DX, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, posY + DY, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, frameHeight, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleScaling)

  BOOST_AUTO_TEST_CASE(RectangleScaling_ValidArgument_NoExceptions)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    const double width = rect.getWidth();
    const double height = rect.getHeight();
    const double area = rect.getArea();
    const double x = rect.getCentre().x;
    const double y = rect.getCentre().y;
    const double posX = rect.getFrameRect().pos.x;
    const double posY = rect.getFrameRect().pos.y;
    const double frameWidth = rect.getFrameRect().width;
    const double frameHeight = rect.getFrameRect().height;
    rect.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(rect.getWidth(), width * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getHeight(), height * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getArea(), area * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().x, x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().y, y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, posX, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, posY, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, frameWidth * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, frameHeight * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleScaling_NegativeCoefficient_ExceptionThrow)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    BOOST_CHECK_THROW(rect.scale(INVALID_COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RectangleScaling_ZeroAsCoefficient_NoException)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    BOOST_CHECK_NO_THROW(rect.scale(0.0));
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleGetters)

  BOOST_AUTO_TEST_CASE(RectangleCheckGettersWork_ValidArgument_NoExceptions)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getArea(), AREA, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleRotate)

BOOST_AUTO_TEST_CASE(RectangleRotate_ValidArgument_NoExceptions)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    BOOST_CHECK_NO_THROW(rect.rotate(ANGLE));
    BOOST_CHECK_CLOSE(rect.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, 7.77817459, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, 7.77817459, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleRotate_ZeroAsParameter_NoExceptions)
  {
    gorshechnikov::Rectangle rect(WIDTH, HEIGHT, CENTER);
    BOOST_CHECK_NO_THROW(rect.rotate(0));
    BOOST_CHECK_CLOSE(rect.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rect.getWidth(), WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rect.getHeight(), HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, CENTER.y, EPSILON);
  }
BOOST_AUTO_TEST_SUITE_END()
