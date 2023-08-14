#pragma once

#include <list>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

namespace sfinae {

///////////////////// integral ////////////////////////
/**
 * @brief template alias is used to check if an input variable is an integral type.
 * @details
 * https://en.cppreference.com/w/cpp/types/is_integral
 * if T is the type bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long
 * long, or any implementation-defined extended integer types, including any signed, unsigned, and
 * cv-qualified variants. Otherwise, value is equal to false.
 * @tparam T Input variable to be checked.
 * @return true If variable is an integral type.
 * @return false Otherwise.
 */
template <typename T>
using enable_if_integral =
    std::enable_if_t<std::is_integral_v<T>, int>; // or std::numeric_limits<T>::is_integer

//////////////////// string /////////////////////////
// // v0
// template<typename ItemType>
// auto func(ItemType &i) -> decltype(std::to_string(i), void())
// {
//      std::cout << std::to_string(i);
// }

// // v1
// template <typename T> using enable_if_string = std::enable_if_t<std::is_same_v<std::decay_t<T>,
// std::string>, int>;

// v2 based on https://habr.com/ru/articles/645321/
namespace details {

template <typename maybe_string_t>
inline constexpr bool is_string = std::is_convertible_v<maybe_string_t, std::string>;

template <>
inline constexpr bool is_string<std::string_view> = true; // 'cause is not implicitly convertible to

} // namespace details

/**
 * @brief template alias is used to check if an input variable is a string-like type.
 * @details
 * string-like type: const char *, const char[], std::string, std::string_view, ...
 * @tparam T Input variable to be checked.
 * @return true If variable is a string-like type.
 * @return false Otherwise.
 */
template <typename T> using enable_if_string = std::enable_if_t<details::is_string<T>, int>;

///////////////////// container ////////////////////////

// // v0
// vector || list
// template <typename T> struct is_vector_or_list : std::false_type {};
// template <typename T> struct is_vector_or_list<std::vector<T>> : std::true_type {};
// template <typename T> struct is_vector_or_list<std::list<T>> : std::true_type {};
// template <typename T> inline constexpr bool is_vector_or_list_v = is_vector_or_list<T>::value;
// template <typename T> using enable_if_vector_or_list = std::enable_if_t<is_vector_or_list_v<T>, int>;
// + for std::forward_list, std::array, ...

// v1 Container is iterable (input) but not string like type
namespace details {

// template <typename T, typename = void> struct is_input_iterator : std::false_type {};
// template <typename T>
// struct is_input_iterator<T,
//                          std::void_t<decltype(++std::declval<T &>()), // incrementable,
//                                      decltype(*std::declval<T &>()),  // dereferencable,
//                                      decltype(std::declval<T &>() == std::declval<T &>())>> // comparable
//     : std::true_type {};
template <typename T, class = void> struct is_container : std::false_type {};
template <typename T> struct is_container<T, std::void_t<typename T::iterator>> : std::true_type {};

} // namespace details

/**
 * @brief template alias is used to check if an input variable is a container but not string-like type.
 * @tparam T Input variable to be checked.
 * @return true If variable is a container type.
 * @return false Otherwise.
 */
template <typename T>
using enable_if_container =
    std::enable_if_t<!details::is_string<T> && details::is_container<T>::value, int>;

///////////////////////// tuple /////////////////////////////
namespace details {

template <typename T> struct is_tuple : std::false_type {};

template <typename... U> struct is_tuple<std::tuple<U...>> : std::true_type {};

template <typename T> inline constexpr bool is_tuple_v = is_tuple<T>::value;

} // namespace details

/**
 * @brief template alias is used to check if an input variable is a std::tuple.
 * @tparam T Input variable to be checked.
 * @return true If variable is a std::tuple.
 * @return false Otherwise.
 */
template <typename T> using enable_if_tuple = std::enable_if_t<details::is_tuple_v<T>, int>;

} // namespace sfinae
