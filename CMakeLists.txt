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

include(GNUInstallDirs)

add_compile_options(-Wall -Werror -O2)

add_subdirectory(src)

install(FILES
  authors copying goat_tracker_commands.pdf readme.txt readme_resid.txt
  readme_sdl.txt
  DESTINATION ${CMAKE_INSTALL_DOCDIR})