#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <tuple>
// #include <typeinfo>

#include "traits.hpp"
#include "utils/print_helpers.hpp"

namespace sfinae {

/**
 * @brief for integral @p ip output to @p out ( @p sep )-separated byte-by-byte repr of integral type @p ip.
 * @details
 * If address is integer than it's output byte-by-byte, unsigned, high byte first,
 * followed by `.` as a separator.
 * @par Examples:
 * @code{.cpp}
 * print_ip( int8_t{-1} ); // 255
 * print_ip( int16_t{0} ); // 0.0
 * print_ip( int32_t{2130706433} ); // 127.0.0.1
 * print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
 * @endcode
 * @tparam T integral
 */
template <typename T, enable_if_integral<T> = 0>
void print_ip(T &&ip /** integral */, std::ostream &out /** output stream */ = std::cout,
              [[maybe_unused]] const char *sep /** separator */ = ".") {
  static constexpr size_t tsz = sizeof(T);
  // todo: make compile time resolved ... without dot at the end
  for (size_t i = tsz; i--;) {
    out << static_cast<std::uint16_t>(ip >> (i * std::numeric_limits<unsigned char>::digits) &
                                      std::numeric_limits<unsigned char>::max());
    if (i)
      out << sep;
  }
  PPF(out);
}

/**
 * @brief for string @p ip output to @p out @p ip as is.
 * @details
 * If address is string than it's output as is.
 * @par Examples:
 * @code{.cpp}
 * print_ip( std::string{“Hello, World!”} ); // Hello, World!
 * @endcode
 * @tparam T string
 */
template <typename T, enable_if_string<T> = 0>
void print_ip(T &&ip /** string */, std::ostream &out /** output stream */ = std::cout,
              [[maybe_unused]] const char *sep /** separator */ = ".") {
  out << ip;
  PPF(out);
}

/**
 * @brief for container @p ip output to @p out @p ip element by element with @p sep - separated.
 * @details
 * If address is (`std::list` or `std::vector`) container than it's output element by element
 * and separated by `.` Elements are displayed as are.
 * @par Examples:
 * @code{.cpp}
 * print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
 * print_ip( std::list<shot>{400, 300, 200, 100} ); // 400.300.200.100
 * @endcode
 * @tparam T container (list, vector, ...)
 */
template <typename T, enable_if_container<T> = 0>
void print_ip(T &&ip /** container */, std::ostream &out /** output stream */ = std::cout,
              [[maybe_unused]] const char *sep /** separator */ = ".") {
  auto &&from = ip.begin();
  auto &&to = ip.end();
  if (from != to) {
    out << *from;
    for (auto &&it = ++from; it != to; ++it) {
      out << sep << *it;
    }
  }
  PPF(out);
}

////////////// tuple printing ///////////////////

template <class T, std::size_t... Is>
void _print_tuple_impl(T &&t, std::index_sequence<Is...>, std::ostream &out, const char *sep) {
  ((out << (Is == 0 ? "" : sep) << std::get<Is>(t)), ...);
}

/**
 * @brief for string @p ip output to @p out @p ip element by element with @p sep - separeted.
 * @details
 * * If address is tuple цшер all member types are the same than it's output member by member and separated
 * by `.` Members are displayed as are. If tuple member types are not the same than error should be output
 * at compile time.
 * @par Examples:
 * @code{.cpp}
 * print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
 * @endcode
 * @tparam T tuple
 */
template <typename T, enable_if_tuple<T> = 0>
void print_ip(T &&ip /** tuple */, std::ostream &out = std::cout, [[maybe_unused]] const char *sep = ".") {
  _print_tuple_impl(std::forward<T>(ip), std::make_index_sequence<std::tuple_size_v<T>>{}, out, sep);
  PPF(out);
}

} // namespace sfinae
