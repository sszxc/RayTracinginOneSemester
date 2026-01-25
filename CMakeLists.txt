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

# ---- Tests (Catch2) ----
enable_testing()

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_executable(test_camera
  tests/test_camera.cpp
)

target_include_directories(test_camera PRIVATE ${CMAKE_SOURCE_DIR}/include)

if(glm_FOUND)
  target_link_libraries(test_camera PRIVATE glm::glm)
endif()

target_link_libraries(test_camera PRIVATE Catch2::Catch2WithMain)

add_test(NAME CameraTests COMMAND test_camera)
