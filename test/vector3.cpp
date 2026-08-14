#include "../cass_linear.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Vector3 construction and conversions", "[Vector3]") {
  SECTION("Default constructor creates zero vector") {
    cass::Vector3<int> v;
    REQUIRE(v.x == 0);
    REQUIRE(v.y == 0);
    REQUIRE(v.z == 0);
  }

  SECTION("Component constructor initializes correctly") {
    cass::Vector3<float> v(1.0f, 2.0f, 3.0f);
    REQUIRE(v.x == 1.0f);
    REQUIRE(v.y == 2.0f);
    REQUIRE(v.z == 3.0f);
  }

  SECTION("Construction from Vector2 and z component") {
    cass::Vector2<double> v2(4.0, 5.0);
    cass::Vector3<double> v3(v2, 6.0);
    REQUIRE(v3.x == 4.0);
    REQUIRE(v3.y == 5.0);
    REQUIRE(v3.z == 6.0);
  }

  SECTION("Conversion constructor converts scalar types") {
    cass::Vector3<int> vInt(1, 2, 3);
    cass::Vector3<double> vDouble(vInt);
    REQUIRE(vDouble.x == 1.0);
    REQUIRE(vDouble.y == 2.0);
    REQUIRE(vDouble.z == 3.0);
  }
}

TEST_CASE("Vector3 arithmetic operations", "[Vector3]") {
  SECTION("Addition and Subtraction of vectors") {
    cass::Vector3<int> a(1, 2, 3);
    cass::Vector3<int> b(4, 5, 6);

    auto sum = a + b;
    REQUIRE(sum.x == 5);
    REQUIRE(sum.y == 7);
    REQUIRE(sum.z == 9);

    auto diff = b - a;
    REQUIRE(diff.x == 3);
    REQUIRE(diff.y == 3);
    REQUIRE(diff.z == 3);
  }

  SECTION("Scalar operations and unary negation") {
    cass::Vector3<double> v(2.0, -3.0, 4.0);
    auto neg = -v;
    REQUIRE(neg.x == -2.0);
    REQUIRE(neg.y == 3.0);
    REQUIRE(neg.z == -4.0);

    auto scaled = v * 3.0;
    REQUIRE(scaled.x == 6.0);
    REQUIRE(scaled.y == -9.0);
    REQUIRE(scaled.z == 12.0);
  }

  SECTION("In-place compound assignment") {
    cass::Vector3<int> v(1, 1, 1);
    v += cass::Vector3<int>(2, 3, 4);
    REQUIRE(v.x == 3);
    REQUIRE(v.y == 4);
    REQUIRE(v.z == 5);

    v -= cass::Vector3<int>(1, 1, 1);
    REQUIRE(v.x == 2);
    REQUIRE(v.y == 3);
    REQUIRE(v.z == 4);
  }
}

TEST_CASE("Vector3 geometry operations", "[Vector3]") {
  SECTION("Dot product") {
    cass::Vector3<double> a(1.0, 2.0, 3.0);
    cass::Vector3<double> b(4.0, -5.0, 6.0);
    REQUIRE(a.dot(b) == 12.0);
  }

  SECTION("Cross product") {
    cass::Vector3<double> i(1.0, 0.0, 0.0);
    cass::Vector3<double> j(0.0, 1.0, 0.0);
    auto k = i.cross(j);

    REQUIRE_THAT(k.x, Catch::Matchers::WithinRel(0.0, 0.0001));
    REQUIRE_THAT(k.y, Catch::Matchers::WithinRel(0.0, 0.0001));
    REQUIRE_THAT(k.z, Catch::Matchers::WithinRel(1.0, 0.0001));
  }

  SECTION("Magnitude and Normalization") {
    cass::Vector3<double> v(2.0, 3.0, 6.0); // magnitude = sqrt(4 + 9 + 36) = sqrt(49) = 7
    REQUIRE_THAT(v.magnitude(), Catch::Matchers::WithinRel(7.0, 0.0001));

    auto norm = v.normalize();
    REQUIRE_THAT(norm.x, Catch::Matchers::WithinRel(2.0 / 7.0, 0.0001));
    REQUIRE_THAT(norm.y, Catch::Matchers::WithinRel(3.0 / 7.0, 0.0001));
    REQUIRE_THAT(norm.z, Catch::Matchers::WithinRel(6.0 / 7.0, 0.0001));
    REQUIRE_THAT(norm.magnitude(), Catch::Matchers::WithinRel(1.0, 0.0001));
  }
}
