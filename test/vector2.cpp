#include "../cass_linear.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace cass::linear;

TEST_CASE("Vector2 construction and conversions", "[Vector2]") {
  SECTION("Default constructor creates zero vector") {
    Vector2<int> v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
  }

  SECTION("Component constructor initializes correctly") {
    Vector2<float> v(3.5f, -2.1f);
    REQUIRE(v.x == 3.5f);
    REQUIRE(v.y == -2.1f);
  }

  SECTION("Conversion constructor converts scalar types") {
    Vector2<int> vInt(3, 4);
    Vector2<double> vDouble(vInt);
    REQUIRE(vDouble.x == 3.0);
    REQUIRE(vDouble.y == 4.0);
  }
}

TEST_CASE("Vector2 arithmetic operations", "[Vector2]") {
  SECTION("Addition of vectors") {
    Vector2<int> a(1, 2);
    Vector2<int> b(3, 4);
    auto res = a + b;
    REQUIRE(res.x == 4);
    REQUIRE(res.y == 6);
  }

  SECTION("Addition of scalar") {
    Vector2<int> v(1, 2);
    auto res = v + 5;
    REQUIRE(res.x == 6);
    REQUIRE(res.y == 7);
  }

  SECTION("Unary negation") {
    Vector2<int> v(3, -4);
    auto res = -v;
    REQUIRE(res.x == -3);
    REQUIRE(res.y == 4);
  }

  SECTION("Subtraction of vectors") {
    Vector2<float> a(5.5f, 7.5f);
    Vector2<float> b(2.0f, 3.0f);
    auto res = a - b;
    REQUIRE(res.x == 3.5f);
    REQUIRE(res.y == 4.5f);
  }

  SECTION("Subtraction of scalar") {
    Vector2<int> v(10, 20);
    auto res = v - 3;
    REQUIRE(res.x == 7);
    REQUIRE(res.y == 17);
  }

  SECTION("Scalar multiplication") {
    Vector2<double> v(2.5, -4.0);
    auto res = v * 2.0;
    REQUIRE(res.x == 5.0);
    REQUIRE(res.y == -8.0);
  }

  SECTION("In-place addition and subtraction") {
    Vector2<int> v(1, 2);
    v += Vector2<int>(3, 4);
    REQUIRE(v.x == 4);
    REQUIRE(v.y == 6);

    v -= Vector2<int>(1, 1);
    REQUIRE(v.x == 3);
    REQUIRE(v.y == 5);
  }
}

TEST_CASE("Vector2 geometry operations", "[Vector2]") {
  SECTION("Dot product") {
    Vector2<double> a(1.0, 3.0);
    Vector2<double> b(4.0, -2.0);
    REQUIRE(a.dot(b) == -2.0);
  }

  SECTION("Magnitude") {
    Vector2<double> v(3.0, 4.0);
    REQUIRE_THAT(v.magnitude(), Catch::Matchers::WithinRel(5.0, 0.0001));
  }

  SECTION("Normalization") {
    Vector2<double> v(3.0, 4.0);
    auto norm = v.normalize();
    REQUIRE_THAT(norm.x, Catch::Matchers::WithinRel(0.6, 0.0001));
    REQUIRE_THAT(norm.y, Catch::Matchers::WithinRel(0.8, 0.0001));
    REQUIRE_THAT(norm.magnitude(), Catch::Matchers::WithinRel(1.0, 0.0001));
  }
}

TEST_CASE("Vector2 formatting", "[Vector2]") {
  SECTION("toString function") {
    Vector2<int> v(5, -10);
    REQUIRE(v.toString() == "(5, -10)");
  }
}
