cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wunused-variable -Wunused-parameter -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tinyvec)

# Add test executable
add_executable(main main.cpp)

target_include_directories(main
PRIVATE
  ./
)
