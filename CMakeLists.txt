cmake_minimum_required(VERSION 3.15)
project(fatest)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_executable(fatest converter.c driver.c)