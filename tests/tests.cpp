#include <catch2/catch_test_macros.hpp>

#include "evaluator.h"
#include <stdexcept>

Evaluator ev;
TEST_CASE("Successful Expressions are computed", "[evaluate-success]") {
  REQUIRE(ev.execute("5 + 3 - 2", false) == 6);
  REQUIRE(ev.execute("6*4-10", false) == 14);
  REQUIRE(ev.execute("10/2+7", false) == 12);
  REQUIRE(ev.execute("(2+3)*4", false) == 20);
  REQUIRE(ev.execute("(8/(4-2))+6", false) == 10);
  REQUIRE(ev.execute("((((((4 + 2) * (5 - 3)) + (6 / (2 + 1))) - (9 % (4 + 3))) * (7 + 1)) / 2", false) == 48);
  REQUIRE(ev.execute("3+2^3*2", false) == 19);
  REQUIRE(ev.execute("((3+5)*2)-((4-1)*3)", false) == 7);
  REQUIRE(ev.execute("(3+2)^(2+1)", false) == 125);
  REQUIRE(ev.execute("((3+5)*2)-(6-(4+2))", false) == 16);
}

TEST_CASE("Compute Invalid Expressions", "[evaluate-throw]") {
  CHECK_THROWS(ev.execute("5 + 3 -", false));
  CHECK_THROWS(ev.execute("6*4-10-", false));
  CHECK_THROWS(ev.execute("10/2+7*", false)); // This does throws an exception but Catch doesn't recognize it.
  CHECK_THROWS(ev.execute("(2+3)*4)", false));
  CHECK_THROWS(ev.execute("(8/(4-2+6", false));
  CHECK_THROWS(ev.execute("2^3^2", false));
  CHECK_THROWS(ev.execute("3+2^3*2)", false));
  CHECK_THROWS(ev.execute("((3+5)*2)-((4-1)*3", false));
  CHECK_THROWS(ev.execute("(3+2)^(2+1", false));
  CHECK_THROWS(ev.execute("((3+5)*2)-(6-(4+2", false));
}