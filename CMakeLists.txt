cmake_minimum_required(VERSION 3.17)
project(set)

set(CMAKE_CXX_STANDARD 20)

add_executable(set main.cpp src/Set.h src/UnorderedSet.h src/OrderedSet.h)