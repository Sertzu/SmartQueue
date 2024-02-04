cmake_minimum_required(VERSION 3.14)
project(SmartQueue VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header-only library target
add_library(SmartQueue INTERFACE)
target_include_directories(SmartQueue INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Enable testing and include the tests subdirectory
enable_testing()
add_subdirectory(tests)