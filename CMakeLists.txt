cmake_minimum_required(VERSION 3.24)
project(SP_Iterators)

set(CMAKE_CXX_STANDARD 20)

add_executable(SP_Iterators Demo.cpp sources/MagicalContainer.cpp sources/MagicalContainer.hpp)
