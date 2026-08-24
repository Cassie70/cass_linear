#include "../cass_linear.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace cass::linear;

TEST_CASE("Matrix2 basic operations", "[Matrix2]") {
  SECTION("Default constructor builds identity matrix") {
    Matrix2<float> m;
    REQUIRE(m.m[0][0] == 1.0f);
    REQUIRE(m.m[0][1] == 0.0f);
    REQUIRE(m.m[1][0] == 0.0f);
    REQUIRE(m.m[1][1] == 1.0f);
  }

  SECTION("Matrix negation") {
    Matrix2<int> m;
    auto neg = -m;
    REQUIRE(neg.m[0][0] == -1);
    REQUIRE(neg.m[0][1] == 0);
    REQUIRE(neg.m[1][0] == 0);
    REQUIRE(neg.m[1][1] == -1);
  }

  SECTION("Matrix multiplication") {
    Matrix2<float> a;
    a.m[0][0] = 1;
    a.m[0][1] = 2;
    a.m[1][0] = 3;
    a.m[1][1] = 4;

    Matrix2<float> b;
    b.m[0][0] = 2;
    b.m[0][1] = 0;
    b.m[1][0] = 1;
    b.m[1][1] = 2;

    auto res = a * b;
    // Row 0: 1*2 + 2*1 = 4, 1*0 + 2*2 = 4
    // Row 1: 3*2 + 4*1 = 10, 3*0 + 4*2 = 8
    REQUIRE(res.m[0][0] == 4.0f);
    REQUIRE(res.m[0][1] == 4.0f);
    REQUIRE(res.m[1][0] == 10.0f);
    REQUIRE(res.m[1][1] == 8.0f);
  }

  SECTION("Matrix-Vector multiplication") {
    Matrix2<float> m;
    m.m[0][0] = 2.0f;
    m.m[0][1] = 3.0f;
    m.m[1][0] = 4.0f;
    m.m[1][1] = 5.0f;

    Vector2<float> v(1.0f, 2.0f);
    auto res = m * v;
    REQUIRE(res.x == 8.0f);  // 2*1 + 3*2 = 8
    REQUIRE(res.y == 14.0f); // 4*1 + 5*2 = 14
  }
}

TEST_CASE("Matrix2 transformations", "[Matrix2]") {
  SECTION("Scaling matrix") {
    Matrix2<double> m;
    m.scale(2.0, 3.0);
    REQUIRE(m.m[0][0] == 2.0);
    REQUIRE(m.m[0][1] == 0.0);
    REQUIRE(m.m[1][0] == 0.0);
    REQUIRE(m.m[1][1] == 3.0);
  }

  SECTION("Rotation matrix (90 degrees)") {
    Matrix2<double> m;
    double angle = 3.14159265358979323846 / 2.0; // 90 degrees
    m.rotate(angle);

    Vector2<double> v(1.0, 0.0);
    auto rotated = m * v;
    REQUIRE_THAT(rotated.x, Catch::Matchers::WithinAbs(0.0, 0.0001));
    REQUIRE_THAT(rotated.y, Catch::Matchers::WithinAbs(1.0, 0.0001));
  }
}
