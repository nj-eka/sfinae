#include <gtest/gtest.h>

#include "print_ip.hpp"

using namespace concepts;

TEST(concepts_unit_tests, integral) {
  {
    std::stringstream ss;
    print_ip(std::int8_t{-1}, ss);
    EXPECT_EQ(ss.str(), "255");
  }
  {
    std::stringstream ss;
    print_ip(std::int16_t{0}, ss);
    EXPECT_EQ(ss.str(), "0.0");
  }
  {
    std::stringstream ss;
    print_ip(std::int32_t{2130706433}, ss);
    EXPECT_EQ(ss.str(), "127.0.0.1");
  }
  {
    std::stringstream ss;
    print_ip(std::int64_t{8875824491850138409}, ss);
    EXPECT_EQ(ss.str(), "123.45.67.89.101.112.131.41");
  }
}

TEST(concepts_unit_tests, string_like) {
  {
    std::stringstream ss;
    print_ip(std::string{"Hello, World!"}, ss);
    EXPECT_EQ(ss.str(), "Hello, World!");
  }
  {
    std::stringstream ss;
    print_ip(std::string_view{"Hello, World!"}, ss);
    EXPECT_EQ(ss.str(), "Hello, World!");
  }
  {
    std::stringstream ss;
    print_ip("Hello, World!", ss);
    EXPECT_EQ(ss.str(), "Hello, World!");
  }
}

TEST(concepts_unit_tests, container_like) {
  {
    std::stringstream ss;
    print_ip(std::vector<int>{100, 200, 300, 400}, ss);
    EXPECT_EQ(ss.str(), "100.200.300.400");
  }
  {
    std::stringstream ss;
    print_ip(std::list<short>{400, 300, 200, 100}, ss);
    EXPECT_EQ(ss.str(), "400.300.200.100");
  }
}

TEST(concepts_unit_tests, tuple_like) {
  {
    std::stringstream ss;
    print_ip(std::make_tuple(123, 456, 789, 0), ss);
    EXPECT_EQ(ss.str(), "123.456.789.0");
  }
}