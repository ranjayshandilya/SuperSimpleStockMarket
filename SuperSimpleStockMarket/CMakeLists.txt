cmake_minimum_required (VERSION 3.2.0)

set(This SimpleStockMarket)
project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)

enable_testing()

add_subdirectory(googletest)

add_subdirectory(test)

