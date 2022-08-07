cmake_minimum_required(VERSION 3.22)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Tests
        main.cpp
        CheckersViewTests.h
        CheckersModelTests.h
        CheckersNetTests.h)
target_link_libraries(Tests ${GTEST_LIBRARIES} Core pthread sfml-graphics sfml-window sfml-system)

target_compile_features(Tests PRIVATE cxx_std_20)
