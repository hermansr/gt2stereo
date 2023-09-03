cmake_minimum_required(VERSION 3.12)

project(gt2stereo VERSION 2.77 LANGUAGES C CXX)

if(CMAKE_CROSSCOMPILING)
  find_package(MyGen REQUIRED CONFIG)
endif()

include(CMakeDependentOption)
cmake_dependent_option(GT2_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)
if (GT2_BUILD_WIN32)
  message(STATUS "Including Win32 support")
endif()

add_compile_options(-Wall -O2)

add_subdirectory(src)
