#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>  // for ResultBuilder, CHECK_EQ, TEST_CASE
#include <fmt/format.h>

#include <csd/csd.hpp>  // for to_csd, to_decimal, to_csdfixed

TEST_CASE("test to_csd") {
    fmt::print("test: {}\n", to_csd(28.2, 2));
    CHECK_EQ(to_csd(28.5, 2), "+00-00.+0");
    CHECK_EQ(to_csd(-0.5, 2), "0.-0");
}

TEST_CASE("test to_decimal") {
    CHECK_EQ(to_decimal("+00-00.+"), 28.5);
    CHECK_EQ(to_decimal("0.-"), -0.5);
}

TEST_CASE("test to_csdfixed") {
    CHECK_EQ(to_csdfixed(28.5, 4), "+00-00.+");
    CHECK_EQ(to_csdfixed(-0.5, 4), "0.-");
}

TEST_CASE("test to_decimal") {
    CHECK_EQ(to_decimal("+00-00"), 28);
}

TEST_CASE("test to_csd_i") {
    CHECK_EQ(to_csd_i(28), "+00-00");
}

TEST_CASE("test lcsre") {  // Driver Code
    CHECK_EQ(longest_repeated_substring("+-00+-00+-00+-0"), "+-00+-0"); 
}
