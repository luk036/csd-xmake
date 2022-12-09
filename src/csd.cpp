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
#include <utility>      // for pair

using std::abs;
using std::ceil;
using std::fabs;
using std::log2;
using std::pair;
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
    auto temp = ceil(log2(absnum * 1.5));
    auto [rem, csd] = absnum < 1.0 ? pair{0.0, string{"0"}} : pair{temp, string{""}};

    // int rem; // yes, not yet initialized
    // string csd; // yes, not yet initialzed
    // if (absnum < 1.0) {
    //     rem = 0;
    //     csd = string{"0"};
    // }
    // else {
    //     rem = int(ceil(log2(absnum * 1.5)));
    //     csd = string{""};
    // }
    auto p2n = pow(2.0, rem);
    auto const eps = pow(2.0, -places);
    while (p2n > eps) {
        if (p2n == 1.0) {
            csd += '.';
        }
        p2n /= 2.0;
        auto const det = 1.5 * num;
        if (det > p2n) {
            csd += '+';
            num -= p2n;
        } else {
            if (det < -p2n) {
                csd += '-';
                num += p2n;
            } else {
                csd += '0';
            }
        }
    }
    return csd;
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
    int p2n = static_cast<int>(pow(2.0, ceil(log2(abs(num) * 1.5))));
    string csd("");
    while (p2n > 1) {
        auto const p2n_half = p2n / 2;
        auto const det = 3 * num;
        if (det > p2n) {
            csd += '+';
            num -= p2n_half;
        } else if (det < -p2n) {
            csd += '-';
            num += p2n_half;
        } else {
            csd += '0';
        }
        p2n = p2n_half;
    }
    return csd;
}

/**
 * @brief Convert the CSD string to a decimal
 *
 * @param csd
 * @return double
 */
auto to_decimal(string_view csd) -> double {
    auto num = 0.0;
    auto loc = 0U;
    // for (; i < csd.size(); ++i) {
    //     auto digit = csd[i];
    auto pos = 0U;
    for (auto digit : csd) {
        if (digit == '0') {
            num *= 2.0;
        } else if (digit == '+') {
            num = num * 2.0 + 1.0;
        } else if (digit == '-') {
            num = num * 2.0 - 1.0;
        } else if (digit == '.') {
            loc = pos + 1;
        } else {
            // ignore unknown characters such as '
        }
        ++pos;
    }
    if (loc != 0) {
        num /= std::pow(2.0, csd.size() - loc);
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
        return "0";
    }
    auto const absnum = fabs(num);
    auto temp = ceil(log2(absnum * 1.5));
    auto [rem, csd] = absnum < 1.0 ? pair{0.0, string{"0"}} : pair{temp, string{""}};

    auto p2n = pow(2.0, rem);
    while (p2n > 1.0 || (nnz > 0 && fabs(num) > 1e-100)) {
        if (p2n == 1.0) {
            csd += '.';
        }
        p2n /= 2.0;
        auto const det = 1.5 * num;
        if (det > p2n) {
            csd += '+';
            num -= p2n;
            nnz -= 1;
        } else {
            if (det < -p2n) {
                csd += '-';
                num += p2n;
                nnz -= 1;
            } else {
                csd += '0';
            }
        }
        if (nnz == 0) {
            num = 0.0;
        }
    }
    return csd;
}
