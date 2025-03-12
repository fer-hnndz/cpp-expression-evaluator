#include <catch2/catch_test_macros.hpp>

#include "evaluator.h"

Evaluator ev;
TEST_CASE("Successful Expressions are computed", "[evaluate]") {
  REQUIRE(ev.execute("5 + 3 - 2", false) == 6);
  REQUIRE(ev.execute("6*4-10", false) == 14);
  REQUIRE(ev.execute("10/2+7", false) == 12);
  REQUIRE(ev.execute("(2+3)*4", false) == 20);
  REQUIRE(ev.execute("(8/(4-2))+6", false) == 10);
  REQUIRE(ev.execute("2^3", false) == 8);
  REQUIRE(ev.execute("3+2^3*2", false) == 19);
  REQUIRE(ev.execute("((3+5)*2)-((4-1)*3)", false) == 7);
  REQUIRE(ev.execute("(3+2)^(2+1)", false) == 125);
  REQUIRE(ev.execute("((3+5)*2)-(6-(4+2))", false) == 16);
}