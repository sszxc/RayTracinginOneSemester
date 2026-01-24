cmake_minimum_required(VERSION 3.10)
project(RayTracinginOneSemester)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Compile executable
add_executable(Render src/main.cpp)
