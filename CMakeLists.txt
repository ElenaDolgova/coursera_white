cmake_minimum_required(VERSION 3.8)
project(coursera_white)

set(CMAKE_CXX_STANDARD 17)


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
endif()

include_directories(src)

add_executable(coursera_white algo/Partitioning_souvenirs.cpp)