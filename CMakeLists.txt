cmake_minimum_required(VERSION 3.16)

project(FixedPoint)

find_package(GTest CONFIG REQUIRED)

add_library(fixedpoint INTERFACE)
target_include_directories(fixedpoint INTERFACE include)

add_executable(FixedPointTest
    tests/testFixedPoint.cpp
    tests/testFixedConversion.cpp)

target_link_libraries(FixedPointTest PRIVATE fixedpoint GTest::gmock_main )