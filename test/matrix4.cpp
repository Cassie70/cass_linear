#include "../cass_linear.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace cass::linear;

TEST_CASE("Matrix4 static constructors and basic properties", "[Matrix4]") {
  SECTION("Identity matrix") {
    auto m = Matrix4<float>::identity();
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i == j) {
          REQUIRE(m.m[i][j] == 1.0f);
        } else {
          REQUIRE(m.m[i][j] == 0.0f);
        }
      }
    }
  }

  SECTION("Zero matrix") {
    auto m = Matrix4<float>::zero();
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        REQUIRE(m.m[i][j] == 0.0f);
  }

  SECTION("Diagonal matrix") {
    auto m = Matrix4<float>::diagonal(5.0f);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i == j)
          REQUIRE(m.m[i][j] == 5.0f);
        else
          REQUIRE(m.m[i][j] == 0.0f);
      }
    }
  }

  SECTION("Initializer list constructor") {
    Matrix4<float> m = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    REQUIRE(m.m[0][0] == 1.0f);
    REQUIRE(m.m[0][3] == 4.0f);
    REQUIRE(m.m[3][0] == 13.0f);
    REQUIRE(m.m[3][3] == 16.0f);
  }
}

TEST_CASE("Matrix4 3D Transformations", "[Matrix4]") {
  SECTION("Translation") {
    auto m = Matrix4<double>::identity();
    m.translate(10.0, 20.0, 30.0);

    Vector4<double> p(1.0, 2.0, 3.0, 1.0);
    auto transformed = m * p;
    REQUIRE(transformed.x == 11.0);
    REQUIRE(transformed.y == 22.0);
    REQUIRE(transformed.z == 33.0);
    REQUIRE(transformed.t == 1.0);
  }

  SECTION("Scaling") {
    auto m = Matrix4<double>::identity();
    m.scale(2.0, 3.0, 4.0);

    Vector4<double> p(1.0, 1.0, 1.0, 1.0);
    auto transformed = m * p;
    REQUIRE(transformed.x == 2.0);
    REQUIRE(transformed.y == 3.0);
    REQUIRE(transformed.z == 4.0);
  }

  SECTION("Inverse of a Matrix4") {
    auto m = Matrix4<double>::identity();
    m.translate(5.0, -10.0, 15.0);

    Matrix4<double> copy = m;
    m.inverse();

    auto identityCheck = copy * m;
    REQUIRE_THAT(identityCheck.m[0][0],
                 Catch::Matchers::WithinRel(1.0, 0.0001));
    REQUIRE_THAT(identityCheck.m[1][1],
                 Catch::Matchers::WithinRel(1.0, 0.0001));
    REQUIRE_THAT(identityCheck.m[2][2],
                 Catch::Matchers::WithinRel(1.0, 0.0001));
    REQUIRE_THAT(identityCheck.m[3][3],
                 Catch::Matchers::WithinRel(1.0, 0.0001));
  }

  SECTION("Ortho Projection") {
    auto ortho = Matrix4<float>::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    REQUIRE(ortho.m[0][0] == 1.0f);
    REQUIRE(ortho.m[1][1] == 1.0f);
    REQUIRE(ortho.m[3][3] == 1.0f);
  }
}
