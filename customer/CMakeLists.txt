cmake_minimum_required(VERSION 3.21)
project(customer)

set(CMAKE_CXX_STANDARD 14)

find_package(FMT REQUIRED)
find_package(cJSON REQUIRED)
include_directories(/opt/homebrew/include)

add_executable(customer Customer.h main.cpp)
