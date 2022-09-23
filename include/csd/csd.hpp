#pragma once

#include <string_view>  // for string_view
#include <iosfwd>  // for string
#include <string>  // for basic_string, operator==, operator<<

extern auto to_csd(double num, int places) -> std::string;
extern auto to_csdfixed(double num, unsigned int nnz) -> std::string;
extern auto longest_repeated_substring(std::string_view sv) -> std::string;
extern auto to_decimal(std::string_view csd_str) -> double;
extern auto to_csd_i(int num) -> std::string;

/**
 * @brief Convert the CSD string to a decimal
 *
 * @param csd_str
 * @return int
 */
inline constexpr auto to_decimal_i(std::string_view csd_str) -> int {
    auto num = 0;
    for (auto&& c : csd_str) {
        if (c == '0') {
            num *= 2;
        } else if (c == '+') {
            num = num * 2 + 1;
        } else if (c == '-') {
            num = num * 2 - 1;
        } else {
            // ignore unknown characters such as '
        }
    }
    return num;
}

