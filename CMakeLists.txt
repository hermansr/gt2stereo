cmake_minimum_required(VERSION 3.13)

project(gt2stereo VERSION 2.77 LANGUAGES C CXX)

if(CMAKE_CROSSCOMPILING)
  find_package(MyGen REQUIRED CONFIG)
endif()

find_package(SDL)
if(NOT SDL_FOUND)
  # e.g. Fedora 38 does not provide a SDL CMake config file for MingW64
  message(STATUS "SDL not found using CMake config, falling back to pkg-config")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SDL REQUIRED sdl IMPORTED_TARGET)
  # define an alias target so it can be used with same name as via find_package
  add_library(SDL::SDL ALIAS PkgConfig::SDL)
endif()

if(WIN32)
  add_link_options(-static-libgcc -static-libstdc++ -lssp)
  # -l ssp is to fix issue #2233205 with MinGW64 on Fedora 38
endif()

add_compile_options(-Wall -Werror -O2)

include(GNUInstallDirs)

install(FILES
  authors copying goat_tracker_commands.pdf readme.txt readme_resid.txt
  readme_sdl.txt
  DESTINATION ${CMAKE_INSTALL_DOCDIR}
)

add_subdirectory(src)
