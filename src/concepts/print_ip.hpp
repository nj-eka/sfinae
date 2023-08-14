#pragma once

#include <concepts>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>

#include "concepts.hpp"
#include "utils/print_helpers.hpp"

namespace concepts {

template <std::integral T>
void print_ip(T &&ip /** integral */, std::ostream &out /** output stream */ = std::cout,
              [[maybe_unused]] const char *sep /** separator */ = ".") {
  static constexpr size_t tsz = sizeof(T);
  for (size_t i = tsz; i--;) {
    out << static_cast<std::uint16_t>(ip >> (i * std::numeric_limits<unsigned char>::digits) &
                                      std::numeric_limits<unsigned char>::max());
    if (i)
      out << sep;
  }
  PPF(out);
}

template <string_like T>
void print_ip(T &&ip /** string */, std::ostream &out /** output stream */ = std::cout,
              [[maybe_unused]] const char *sep /** separator */ = ".") {
  out << ip;
  PPF(out);
}

template <container_like T>
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

template <tuple_like T, std::size_t... Is>
void _print_tuple_impl(T &&t, std::index_sequence<Is...>, std::ostream &out, const char *sep) {
  ((out << (Is == 0 ? "" : sep) << std::get<Is>(t)), ...);
}

template <tuple_like T>
void print_ip(T &&ip /** tuple */, std::ostream &out = std::cout, [[maybe_unused]] const char *sep = ".") {
  _print_tuple_impl(std::forward<T>(ip), std::make_index_sequence<std::tuple_size_v<T>>{}, out,
                    sep); // ? std::forward_as_tuple()
  PPF(out);
}

} // namespace concepts
