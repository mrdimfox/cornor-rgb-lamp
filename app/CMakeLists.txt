cmake_minimum_required(VERSION 3.15)

# Add CMake scripts (includes) into scope
list(
    APPEND
    CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/../modules/cmake-helpers/"
    "${CMAKE_CURRENT_LIST_DIR}/cmake"
)

include(zephyr_cmake_helpers_init)

# Application project
# ===================

find_package(Zephyr)

project(app C CXX ASM)
