#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <memory>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "matrix.hpp"

const double EPSILON = 0.000001;
const double RADIUS = 6.8;
const double WIDTH = 6.6;
const double HEIGHT = 4.4;
const gorshechnikov::point_t CENTRE = {4.6, -4.5};
const gorshechnikov::point_t CENTRE1 = {9.1, 67.8};

BOOST_AUTO_TEST_SUITE(MatrixConstructor)

  BOOST_AUTO_TEST_CASE(MatrixConstructor_ValidArgument_NoExceptions)
  {
    std::unique_ptr<gorshechnikov::Matrix> matrix;
    BOOST_CHECK_NO_THROW(matrix = std::make_unique<gorshechnikov::Matrix>());
    BOOST_CHECK_EQUAL(matrix->getCountOfLayers(), 0);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixAdd)

  BOOST_AUTO_TEST_CASE(MatrixAdd_ValidArgument_NoException)
  {
    std::unique_ptr<gorshechnikov::Matrix> matrix = std::make_unique<gorshechnikov::Matrix>();
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle1 = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    BOOST_CHECK_NO_THROW(matrix->add(rect));
    BOOST_CHECK_NO_THROW(matrix->add(circle));
    BOOST_CHECK_NO_THROW(matrix->add(circle1));
    BOOST_CHECK_EQUAL(matrix->getCountOfLayers(), 2);
  }

  BOOST_AUTO_TEST_CASE(MatrixAdd_NullptrAsParameter_ExceptionThrow)
  {
    std::unique_ptr<gorshechnikov::Matrix> matrix = std::make_unique<gorshechnikov::Matrix>();
    BOOST_CHECK_THROW(matrix->add(nullptr), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MatrixIndexing)

  BOOST_AUTO_TEST_CASE(MatrixIndexing_ValidArgument_NoException)
  {
    gorshechnikov::Matrix matrix;
    std::shared_ptr<gorshechnikov::Rectangle> rect = std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE);
    std::shared_ptr<gorshechnikov::Circle> circle1 = std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1);
    matrix.add(rect);
    matrix.add(circle);
    matrix.add(circle1);
    BOOST_CHECK_EQUAL(matrix.getCountOfLayers(), 2);
    BOOST_CHECK_EQUAL(matrix[0][0], rect);
    BOOST_CHECK_EQUAL(matrix[1][0], circle);
    BOOST_CHECK_EQUAL(matrix[0][1], circle1);
  }

  BOOST_AUTO_TEST_CASE(MatrixIndexing_InvalidNumberLayer_ExceptionThrow)
  {
    gorshechnikov::Matrix matrix;
    matrix.add(std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE));
    matrix.add(std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE));
    matrix.add(std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1));
    BOOST_CHECK_EQUAL(matrix.getCountOfLayers(), 2);
    BOOST_CHECK_THROW(matrix[4][0], std::out_of_range);
    BOOST_CHECK_THROW(matrix[12][0], std::out_of_range);
  }
  BOOST_AUTO_TEST_CASE(MatrixIndexing_InvalidNumberOfShape_ExceptionThrow)
  {
    gorshechnikov::Matrix matrix;
    matrix.add(std::make_shared<gorshechnikov::Rectangle>(WIDTH, HEIGHT, CENTRE));
    matrix.add(std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE));
    matrix.add(std::make_shared<gorshechnikov::Circle>(RADIUS, CENTRE1));
    BOOST_CHECK_EQUAL(matrix.getCountOfLayers(), 2);
    BOOST_CHECK_THROW(matrix[0][3], std::out_of_range);
    BOOST_CHECK_THROW(matrix[0][20], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
