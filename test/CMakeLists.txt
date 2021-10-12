cmake_minimum_required (VERSION 3.2)
project (Test)
SET(CMAKE_CXX_STANDARD 11)

find_package (Threads)
add_executable (main test.cpp)
target_link_libraries (main Threads::Threads)

