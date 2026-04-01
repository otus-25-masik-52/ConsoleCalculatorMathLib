cmake_minimum_required(VERSION 3.28)

project(ConsoleCalculatorMathLib VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

add_library(calculator_math INTERFACE)

target_compile_features(calculator_math INTERFACE cxx_std_20)

target_include_directories(calculator_math
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(calculator_math
  INTERFACE
  FILE_SET HEADERS
  BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/calculator-math.h
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(calculator_math
    INTERFACE
    -Wall
    -Wextra
    -Wpedantic
  )
elseif(MSVC)
  target_compile_options(calculator_math
    INTERFACE
    /W4
  )
endif()

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(calculator_tests
  tests/calculator-math-test.cpp
)

target_link_libraries(calculator_tests
  PRIVATE
  calculator_math
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests)