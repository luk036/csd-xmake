#pragma once

#include <iosfwd> // for string
#include <string> // for basic_string, operator==, operator<<

namespace csd {

extern auto to_csd(double num, int places) -> std::string;
extern auto to_csdfixed(double num, unsigned int nnz) -> std::string;
extern auto longest_repeated_substring(const char *sv, size_t n) -> std::string;
extern auto to_decimal(const char *csd) -> double;
extern auto to_decimal_using_switch(const char *csd) -> double;
extern auto to_csd_i(int num) -> std::string;

/**
 * @brief Convert the CSD string to a decimal
 *
 * @param csd
 * @return int
 */
inline auto to_decimal_i(char const *csd) -> int {
  auto num = 0;
  for (;; ++csd) {
    auto digit = *csd;
    if (digit == '0') {
      num = 2 * num;
    } else if (digit == '+') {
      num = 2 * num + 1;
    } else if (digit == '-') {
      num = 2 * num - 1;
    } else if (digit == '\0') {
      break;
    } else {
      exit(1); // unknown characters
    }
  }
  return num;
}
} // namespace csd
