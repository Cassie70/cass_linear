#include "../cass_linear.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace cass::linear;

TEST_CASE("Matrix3 basic operations", "[Matrix3]") {
  SECTION("Default constructor creates identity matrix") {
    Matrix3<float> m;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (i == j) {
          REQUIRE(m.m[i][j] == 1.0f);
        } else {
          REQUIRE(m.m[i][j] == 0.0f);
        }
      }
    }
  }

  SECTION("Matrix-Vector multiplication") {
    Matrix3<double> m;
    Vector3<double> v(2.0, 3.0, 4.0);
    auto res = m * v;
    REQUIRE(res.x == 2.0);
    REQUIRE(res.y == 3.0);
    REQUIRE(res.z == 4.0);
  }

  SECTION("Inverse of identity matrix is identity") {
    Matrix3<double> m;
    m.inverse();
    REQUIRE(m.m[0][0] == 1.0);
    REQUIRE(m.m[1][1] == 1.0);
    REQUIRE(m.m[2][2] == 1.0);
  }

  SECTION("Inverse of a 3x3 matrix") {
    Matrix3<double> m;
    m.m[0][0] = 1;
    m.m[0][1] = 0;
    m.m[0][2] = 2;
    m.m[1][0] = 0;
    m.m[1][1] = 1;
    m.m[1][2] = 0;
    m.m[2][0] = 0;
    m.m[2][1] = 0;
    m.m[2][2] = 1;

    Matrix3<double> original = m;
    m.inverse();

    auto result = original * m;
    REQUIRE_THAT(result.m[0][0], Catch::Matchers::WithinRel(1.0, 0.0001));
    REQUIRE_THAT(result.m[1][1], Catch::Matchers::WithinRel(1.0, 0.0001));
    REQUIRE_THAT(result.m[2][2], Catch::Matchers::WithinRel(1.0, 0.0001));
  }
}

TEST_CASE("Matrix3 transformations", "[Matrix3]") {
  SECTION("2D Translation in Matrix3") {
    Matrix3<double> m;
    m.translate(Vector2<double>(5.0, -3.0));

    Vector3<double> p(1.0, 2.0, 1.0);
    auto transformed = m * p;
    REQUIRE(transformed.x == 6.0);
    REQUIRE(transformed.y == -1.0);
    REQUIRE(transformed.z == 1.0);
  }

  SECTION("Scaling in Matrix3") {
    Matrix3<double> m;
    m.scale(2.0, 4.0);

    Vector3<double> p(3.0, 3.0, 1.0);
    auto transformed = m * p;
    REQUIRE(transformed.x == 6.0);
    REQUIRE(transformed.y == 12.0);
  }
}
