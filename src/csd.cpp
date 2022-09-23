/**
 Canonical Signed Digit Functions

 Handles:
  * Decimals
  *
  *

 eg, +00-00+000.0 or 0.+0000-00+
 Where: '+' is +1
        '-' is -1

 Harnesser
 License: GPL2
*/

#include <cmath>        // for fabs, pow, ceil, log2
#include <iosfwd>       // for string
#include <string>       // for basic_string
#include <string_view>  // for string_view

using std::ceil;
using std::fabs;
using std::abs;
using std::log2;
using std::pow;
using std::string;
using std::string_view;

/**
 * @brief Convert to CSD (Canonical Signed Digit) string representation
 *
 * Original author: Harnesser
 * https://sourceforge.net/projects/pycsd/
 * License: GPL2
 *
 * @param num
 * @param places
 * @return string
 */
auto to_csd(double num, const int places) -> string {
    if (num == 0.0) {
        return "0";
    }
    auto const absnum = fabs(num);
    auto const nn = int(ceil(log2(absnum * 1.5)));
    auto n = absnum < 1.0 ? 0 : nn;
    auto const* const str = absnum < 1.0 ? "0" : "";
    auto csd_str = string(str);
    auto pow2n = pow(2.0, double(n));
    while (n > -places) {
        if (n == 0) {
            csd_str += '.';
        }
        n -= 1;
        auto const pow2n_half = pow2n / 2;
        auto const d = 3.0 * num;
        if (d > pow2n) {
            csd_str += '+';
            num -= pow2n_half;
        } else if (d < -pow2n) {
            csd_str += '-';
            num += pow2n_half;
        } else {
            csd_str += '0';
        }
        pow2n = pow2n_half;
    }
    return csd_str;
}

/**
 * @brief Convert to CSD (Canonical Signed Digit) string representation
 *
 * Original author: Harnesser
 * https://sourceforge.net/projects/pycsd/
 * License: GPL2
 *
 * @param num
 * @param places
 * @return string
 */
auto to_csd_i(int num) -> string {
    if (num == 0) {
        return "0";
    }
    auto const absnum = abs(num);
    auto const nn = int(ceil(log2(absnum * 1.5)));
    auto n = absnum < 1.0 ? 0 : nn;
    auto const* const str = absnum < 1.0 ? "0" : "";
    auto csd_str = string{str};
    auto pow2n = int(pow(2.0, double(n)));
    while (n > 0) {
        n -= 1;
        auto const pow2n_half = pow2n / 2;
        auto const d = 3 * num;
        if (d > pow2n) {
            csd_str += '+';
            num -= pow2n_half;
        } else if (d < -pow2n) {
            csd_str += '-';
            num += pow2n_half;
        } else {
            csd_str += '0';
        }
        pow2n = pow2n_half;
    }
    return csd_str;
}

/**
 * @brief Convert the CSD string to a decimal
 *
 * @param csd_str
 * @return double
 */
auto to_decimal(string_view csd_str) -> double {
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

/**
 * @brief Convert to CSD (Canonical Signed Digit) string representation
 *
 * @param[in] num
 * @param[in] nnz number of non-zero
 * @return string
 */
auto to_csdfixed(double num, unsigned int nnz) -> string {
    if (num == 0.0) {
        return string("0");
    }
    auto const absnum = fabs(num);
    auto const nn = int(ceil(log2(absnum * 1.5)));
    auto n = absnum < 1.0 ? 0 : nn;
    const auto *const str = absnum < 1.0 ? "0" : "";
    auto csd_str = string(str);
    auto pow2n = pow(2.0, double(n - 1));
    while (n > 0 || (nnz > 0 && fabs(num) > 1e-100)) {
        if (n == 0) {
            csd_str += '.';
        }
        n -= 1;
        auto const d = 1.5 * num;
        if (d > pow2n) {
            csd_str += '+';
            num -= pow2n;
            nnz -= 1;
        } else if (d < -pow2n) {
            csd_str += '-';
            num += pow2n;
            nnz -= 1;
        } else {
            csd_str += '0';
        }
        pow2n /= 2.0;
        if (nnz == 0) {
            num = 0.0;
        }
    }
    return csd_str;
}
