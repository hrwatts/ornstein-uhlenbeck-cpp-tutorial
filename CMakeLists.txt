cmake_minimum_required(VERSION 3.20)

project(MonteCarloBrownianMotionTutorial VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)

add_library(project_warnings INTERFACE)
if(MSVC)
  target_compile_options(project_warnings INTERFACE /W4 /permissive-)
else()
  target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

add_executable(ou_tutorial src/main.cpp)
target_include_directories(ou_tutorial PRIVATE third_party)
target_link_libraries(ou_tutorial PRIVATE Python3::Python Python3::NumPy project_warnings)

add_executable(minimal_plot examples/minimal_plot.cpp)
target_include_directories(minimal_plot PRIVATE third_party)
target_link_libraries(minimal_plot PRIVATE Python3::Python Python3::NumPy project_warnings)

if(WIN32)
  string(REPLACE "\\" "/" PYTHON3_EXECUTABLE_PATH "${Python3_EXECUTABLE}")
  target_compile_definitions(ou_tutorial PRIVATE PYTHON3_EXECUTABLE_PATH=\"${PYTHON3_EXECUTABLE_PATH}\")
  target_compile_definitions(minimal_plot PRIVATE PYTHON3_EXECUTABLE_PATH=\"${PYTHON3_EXECUTABLE_PATH}\")
  # Suppress noisy warnings from third-party matplotlib-cpp and NumPy headers.
  target_compile_options(ou_tutorial PRIVATE /wd4127 /wd4244)
  target_compile_options(minimal_plot PRIVATE /wd4127 /wd4244)
endif()
