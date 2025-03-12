#include <catch2/catch_test_macros.hpp>

#include "evaluator.h"

Evaluator ev;
TEST_CASE("Successful Expressions are computed", "[evaluate]") { REQUIRE(ev.execute("5 + 3 - 2", false) == 6); }