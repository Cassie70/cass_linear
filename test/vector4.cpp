#include "../cass_linear.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace cass::linear;

TEST_CASE("Vector4 construction and conversions", "[Vector4]") {
  SECTION("Default constructor creates zero vector") {
    Vector4<int> v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
    REQUIRE(v.z == 0);
    REQUIRE(v.t == 0);
  }

  SECTION("Component constructor initializes correctly") {
    Vector4<float> v(1.0f, 2.0f, 3.0f, 4.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
    REQUIRE(v.t == 4.0f);
  }

  SECTION("Construction from Vector3 and t component") {
    Vector3<double> v3(1.0, 2.0, 3.0);
    Vector4<double> v4(v3, 4.0);
    REQUIRE(v4.x == 1.0);
    REQUIRE(v4.y == 2.0);
    REQUIRE(v4.z == 3.0);
    REQUIRE(v4.t == 4.0);
  }
}

TEST_CASE("Vector4 arithmetic and geometric operations", "[Vector4]") {
  SECTION("Addition and Subtraction") {
    Vector4<int> a(1, 2, 3, 4);
    Vector4<int> b(5, 6, 7, 8);

    auto sum = a + b;
    REQUIRE(sum.x == 6);
    REQUIRE(sum.y == 8);
    REQUIRE(sum.z == 10);
    REQUIRE(sum.t == 12);

    auto diff = b - a;
    REQUIRE(diff.x == 4);
    REQUIRE(diff.y == 4);
    REQUIRE(diff.z == 4);
    REQUIRE(diff.t == 4);
  }

  SECTION("Dot product, Magnitude and Normalization") {
    Vector4<double> v(1.0, 1.0, 1.0, 1.0); // magnitude = sqrt(4) = 2
    REQUIRE(v.dot(v) == 4.0);
    REQUIRE_THAT(v.magnitude(), Catch::Matchers::WithinRel(2.0, 0.0001));

    auto norm = v.normalize();
    REQUIRE_THAT(norm.x, Catch::Matchers::WithinRel(0.5, 0.0001));
    REQUIRE_THAT(norm.y, Catch::Matchers::WithinRel(0.5, 0.0001));
    REQUIRE_THAT(norm.z, Catch::Matchers::WithinRel(0.5, 0.0001));
    REQUIRE_THAT(norm.t, Catch::Matchers::WithinRel(0.5, 0.0001));
    REQUIRE_THAT(norm.magnitude(), Catch::Matchers::WithinRel(1.0, 0.0001));
  }
}
