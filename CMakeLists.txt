cmake_minimum_required(VERSION 3.10)
project(RayTracinginOneSemester)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# import Polyscope
include(FetchContent)
FetchContent_Declare(
  polyscope
  GIT_REPOSITORY https://github.com/nmwsharp/polyscope.git
  GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(polyscope)

add_executable(Render
  src/main.cpp
)

find_package(glm QUIET)
if(glm_FOUND)
  target_link_libraries(Render PRIVATE glm::glm)
endif()

# Polyscope automatically links OpenGL, GLFW, and other dependencies
target_link_libraries(Render PRIVATE polyscope)
