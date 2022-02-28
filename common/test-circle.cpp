#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "base-types.hpp"
#include "circle.hpp"


const double EPSILON = 0.000001;
const double RADIUS = 5.5;
const double INVALID_RADIUS = -0.89;
const gorshechnikov::point_t CENTER = {2.3, 4.5};
const gorshechnikov::point_t POINT = {7.1, 9.2};
const double DX = 7.1;
const double DY = 9.2;
const double COEFFICIENT = 1.5;
const double INVALID_COEFFICIENT = -6.7;
const double AREA = 5.5 * 5.5 * M_PI;
const double ANGLE = 8.45;

BOOST_AUTO_TEST_SUITE(CircleConstructor)

  BOOST_AUTO_TEST_CASE(CircleConstructor_ValidArguments_NoExceptions)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    const double radius = circle.getRadius();
    const double area = circle.getArea();
    const double frameWidth = circle.getFrameRect().width;
    const double frameHeight = circle.getFrameRect().height;
    BOOST_CHECK_CLOSE(circle.getRadius(), radius, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CircleConstructor_NegativeRadius_ExceptionThrow)
  {
    BOOST_CHECK_THROW(gorshechnikov::Circle(INVALID_RADIUS, CENTER), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CircleConstructor_ZeroAsRadius_ExceptionThrow)
  {
    BOOST_CHECK_NO_THROW(gorshechnikov::Circle(0.0, CENTER));
  }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(CircleMoving)

  BOOST_AUTO_TEST_CASE(CircleMovingInPoint_ValidArgument_NoExceptions)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    const double radius = circle.getRadius();
    const double area = circle.getArea();
    const double frameWidth = circle.getFrameRect().width;
    const double frameHeight = circle.getFrameRect().height;
    circle.move(POINT);
    BOOST_CHECK_CLOSE(circle.getRadius(), radius, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().x, POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().y, POINT.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, POINT.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, POINT.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CircleMovingOnAxes_ValidArgument_NoExceptions)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    const double radius = circle.getRadius();
    const double area = circle.getArea();
    const double x = circle.getCentre().x;
    const double y = circle.getCentre().y;
    const double posX = circle.getFrameRect().pos.x;
    const double posY = circle.getFrameRect().pos.y;
    const double frameWidth = circle.getFrameRect().width;
    const double frameHeight = circle.getFrameRect().height;
    circle.move(DX, DY);
    BOOST_CHECK_CLOSE(circle.getRadius(), radius, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), area, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().x, x + DX, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().y, y + DY, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, posX + DX, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, posY + DY, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(CircleScaling)

  BOOST_AUTO_TEST_CASE(CircleScaling_PositiveCoefficient_NoExceptions)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    const double radius = circle.getRadius();
    const double area = circle.getArea();
    const double x = circle.getCentre().x;
    const double y = circle.getCentre().y;
    const double posX = circle.getFrameRect().pos.x;
    const double posY = circle.getFrameRect().pos.y;
    const double frameWidth = circle.getFrameRect().width;
    const double frameHeight = circle.getFrameRect().height;
    circle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(circle.getRadius(), radius * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), area * COEFFICIENT * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().x, x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().y, y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, posX, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, posY, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameWidth * COEFFICIENT, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameHeight * COEFFICIENT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CircleScaling_NegativeCoefficient_ExceptionThrow)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    BOOST_CHECK_THROW(circle.scale(INVALID_COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CircleScaling_ZeroAsCoefficient_NoException)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    BOOST_CHECK_NO_THROW(circle.scale(0.0));
  }

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(CircleGetters)

  BOOST_AUTO_TEST_CASE(CircleCheckGettersWork_ValidArgument_NoExceptions)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleRotate)

BOOST_AUTO_TEST_CASE(CircleRotate_ValidArgument_NoExceptions)
  {
    gorshechnikov::Circle circle(RADIUS, CENTER);
    circle.rotate(ANGLE);
    BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
