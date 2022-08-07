cmake_minimum_required(VERSION 3.22)

add_executable(Checkers main.cpp)
target_link_libraries(Checkers Core pthread sfml-graphics sfml-window sfml-system)

target_compile_features(Checkers PRIVATE cxx_std_20)
