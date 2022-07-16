#pragma once

#include <cmath>        // for fabs, pow, ceil, log2
#include <string_view>  // for basic_string, operator==, operator<<

/**
 * @brief Convert the CSD string to a decimal
 *
 * @param csd_str
 * @return double
 */
inline constexpr auto to_decimal(std::string_view csd_str) -> double {
    auto num = 0.0;
    auto loc = 0U;
    auto i = 0U;
    // for (; i < csd_str.size(); ++i) {
    //     auto c = csd_str[i];
    for (auto&& c : csd_str) {
        if (c == '0') {
            num *= 2.0;
        } else if (c == '+') {
            num = num * 2.0 + 1.0;
        } else if (c == '-') {
            num = num * 2.0 - 1.0;
        } else if (c == '.') {
            loc = i + 1;
        } else {
            // ignore unknown characters such as '
        }
        ++i;
    }
    if (loc != 0) {
        num /= std::pow(2.0, double(csd_str.size() - loc));
    }
    return num;
}

#include <iosfwd>  // for string
#include <string>  // for basic_string, operator==, operator<<

extern auto to_csd(double num, int places) -> std::string;
extern auto to_csdfixed(double num, unsigned int nnz) -> std::string;
