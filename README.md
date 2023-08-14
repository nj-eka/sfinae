# sfinae
Course c++ developer: hw4 - sfinae

## task
- [pdf](04_homework.pdf)

## Install
```bash
> git clone https://github.com/nj-eka/sfinae.git
> cd sfinae

# config example
> cmake -B ./build -S . -DPRINT_PRETTY_FUNCTION=ON \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTING=ON \
    -DCMAKE_CXX_FLAGS="-g -O0 -fsanitize=undefined -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer"

# build
> cmake --build ./build

# install (* skipped)
> cmake --build ./build --target install

# run tests
> ctest --test-dir build -T Test --verbose
...
1: [==========] Running 8 tests from 2 test suites.
1: [----------] Global test environment set-up.
1: [----------] 4 tests from sfinae_unit_tests
1: [ RUN      ] sfinae_unit_tests.enable_if_integral
1: [       OK ] sfinae_unit_tests.enable_if_integral (0 ms)
1: [ RUN      ] sfinae_unit_tests.enable_if_string
1: [       OK ] sfinae_unit_tests.enable_if_string (0 ms)
1: [ RUN      ] sfinae_unit_tests.enable_if_container
1: [       OK ] sfinae_unit_tests.enable_if_container (0 ms)
1: [ RUN      ] sfinae_unit_tests.enable_if_tuple
1: [       OK ] sfinae_unit_tests.enable_if_tuple (0 ms)
1: [----------] 4 tests from sfinae_unit_tests (0 ms total)
1: 
1: [----------] 4 tests from concepts_unit_tests
1: [ RUN      ] concepts_unit_tests.integral
1: [       OK ] concepts_unit_tests.integral (0 ms)
1: [ RUN      ] concepts_unit_tests.string_like
1: [       OK ] concepts_unit_tests.string_like (0 ms)
1: [ RUN      ] concepts_unit_tests.container_like
1: [       OK ] concepts_unit_tests.container_like (0 ms)
1: [ RUN      ] concepts_unit_tests.tuple_like
1: [       OK ] concepts_unit_tests.tuple_like (0 ms)
1: [----------] 4 tests from concepts_unit_tests (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 8 tests from 2 test suites ran. (2 ms total)
1: [  PASSED  ] 8 tests.
1/1 Test #1: hw4_gtest ........................   Passed    0.02 sec

100% tests passed, 0 tests failed out of 1

```