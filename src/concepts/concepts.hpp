#pragma once

#include <concepts>
#include <list>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

namespace concepts {

// template <typename U, typename T>
// concept DecaysTo = std::same_as<std::decay_t<U>, T>;

template <typename T, typename... U>
concept _IsAnyOf = (std::same_as<T, U> || ...);

template <typename T>
concept string_like = std::same_as<T, std::string_view> || std::convertible_to<T, std::string> ||
                      _IsAnyOf<std::remove_cvref_t<std::remove_pointer_t<std::decay_t<T>>>, char, wchar_t>;

template <typename T>
concept container_like = !string_like<T> && requires(const T &container) {
  *(++container.begin());
  container.begin() == container.end();
};

// based on https://stackoverflow.com/questions/68443804/c20-concept-to-check-tuple-like-types
template <class T, std::size_t N>
concept has_tuple_element = requires(T t) {
  typename std::tuple_element_t<N, std::remove_const_t<T>>;
  { get<N>(t) } -> std::convertible_to<const std::tuple_element_t<N, T> &>;
};

template <class T>
concept tuple_like = !std::is_reference_v<T> && requires(T t) {
  typename std::tuple_size<T>::type;
  requires std::derived_from<std::tuple_size<T>, std::integral_constant<std::size_t, std::tuple_size_v<T>>>;
} && []<std::size_t... N>(std::index_sequence<N...>) {
  return (has_tuple_element<T, N> && ...);
}(std::make_index_sequence<std::tuple_size_v<T>>());

} // namespace concepts
