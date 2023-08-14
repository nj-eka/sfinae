/**
 * @package hw4
 * @author jn108
 * @brief applying sfinae/concept to overloading function print_ip as hw4 (course c++ developer)
 * @version 0.1
 * @date 2023-08
 * @copyright Copyright (c) 2023
 */
#include <cstdint>
#include <iostream>

#include "concepts/print_ip.hpp"
#include "sfinae/print_ip.hpp"
#include "utils/print_helpers.hpp"

int main() {
  {
    using namespace sfinae;
    SHOW(print_ip(std::int8_t{-1}));
    SHOW(print_ip(std::int16_t{0}));
    SHOW(print_ip(std::int32_t{2130706433}));
    SHOW(print_ip(std::int64_t{8875824491850138409}));
    SHOW(print_ip(std::string{"Hello, World!"}));
    SHOW(print_ip(std::vector<int>{100, 200, 300, 400}));
    SHOW(print_ip(std::list<short>{400, 300, 200, 100}));
    SHOW(print_ip(std::make_tuple(123, 456, 789, 0)));
  }

  {
    using namespace concepts;
    SHOW(print_ip(std::int8_t{-1}));
    SHOW(print_ip(std::int16_t{0}));
    SHOW(print_ip(std::int32_t{2130706433}));
    SHOW(print_ip(std::int64_t{8875824491850138409}));
    SHOW(print_ip(std::string{"Hello, World!"}));
    SHOW(print_ip(std::vector<int>{100, 200, 300, 400}));
    SHOW(print_ip(std::list<short>{400, 300, 200, 100}));
    SHOW(print_ip(std::make_tuple(123, 456, 789, 0)));
  }

  return 0;
}