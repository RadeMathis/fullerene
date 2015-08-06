cmake_minimum_required(VERSION 2.8)

PROJECT(fullgene)

add_definitions(-std=c++11 -Wall -Wextra -pg -g)

add_subdirectory(./include)
add_subdirectory(./src)
add_subdirectory(./lib)
