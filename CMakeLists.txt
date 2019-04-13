cmake_minimum_required(VERSION 3.13)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g -Wextra -Werror -Wall -pedantic")

add_executable(algorithms module_2/seminars/HashTable.cpp)
add_executable(my_hash module_2/1-2.cpp)