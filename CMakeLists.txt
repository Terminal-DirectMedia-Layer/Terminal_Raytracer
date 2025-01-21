cmake_minimum_required(VERSION 3.27.7)

project(
    Raymenteur
    VERSION     0.1
    LANGUAGES   CXX
)

set(CMAKE_CXX_STANDARD 20)

set(RAYTRACER_CORE_DIR           ${CMAKE_CURRENT_SOURCE_DIR}/src/core)
set(RAYTRACER_INCLUDE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RAYTRACER_PLUGIN_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin)
set(RAYTRACER_DISPLAY_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/src/display)

set(RAYTRACER_OUTPUT_PLUGIN_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/plugins)
set(RAYTRACER_OUTPUT_DISPLAY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/displays)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd/TDL_Terminal-DirectMedia-Library/include ${LIBEVDEV_INCLUDE_DIRS})

include(${RAYTRACER_INCLUDE_DIR}/CMakeLists.txt)
include(${RAYTRACER_CORE_DIR}/CMakeLists.txt)
include(${RAYTRACER_DISPLAY_DIR}/CMakeLists.txt)
include(${RAYTRACER_PLUGIN_DIR}/CMakeLists.txt)