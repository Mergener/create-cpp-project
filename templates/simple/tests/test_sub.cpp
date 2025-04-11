#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "lib.h"

using namespace project_name;

TEST_CASE("Testing the sub function") {
    CHECK(sub(1, 2) == -1);
    CHECK(sub(2, 4) == -2);
    CHECK(sub(3, 9) == -6);
}