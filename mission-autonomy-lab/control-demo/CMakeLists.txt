
# Require CMake version 3.16 or newer.
# This ensures the features we use are supported.
cmake_minimum_required(VERSION 3.16)


# Define the project.
#
# ControlDemo: Project name
# VERSION 1.0: Project version metadata
# LANGUAGES CXX: We are using C++
project(ControlDemo VERSION 1.0 LANGUAGES CXX)


# Compile using the C++17 language standard.
set(CMAKE_CXX_STANDARD 17)

# Require C++17 rather than silently falling back.
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# =============================================
# 1. BUILD THE PID CONTROLLER LIBRARY
# =============================================

# Define a library target named pid_controller.
#
# CMake compiles pid_controller.cpp into a library
# that other executables can link against.
#
# By default, this is typically a static library,
# although the actual type also depends on
# BUILD_SHARED_LIBS.
add_library(pid_controller
    src/pid_controller.cpp
)


# Tell CMake where to find our header files.
#
# PUBLIC means:
# - The pid_controller library uses this directory.
# - Any target linking to this library also
#   inherits this include directory.
#
# This lets main.cpp use:
# #include "pid_controller.h"
target_include_directories(pid_controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# =============================================
# 2. BUILD THE SIMULATION EXECUTABLE
# =============================================

# Create an executable named control_demo.
#
# main.cpp contains the main() entry point.
add_executable(control_demo
    src/main.cpp
)


# =============================================
# 3. LINK LIBRARY TO EXECUTABLE
# =============================================

# Connect the executable to the PID library.
#
# PRIVATE means this dependency is only needed
# internally by control_demo.
#
# The executable can now call functions implemented
# in pid_controller.cpp.
target_link_libraries(control_demo PRIVATE
    pid_controller
)
