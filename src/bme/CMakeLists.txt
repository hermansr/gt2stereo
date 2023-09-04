cmake_minimum_required(VERSION 3.13)

add_library(bme OBJECT
  bme.c
  bme_end.c
  bme_gfx.c
  bme_io.c
  bme_kbd.c
  bme_mou.c
  bme_snd.c
  bme_win.c
)
target_include_directories(bme PUBLIC .)
target_link_libraries(bme PUBLIC SDL::SDL)

# only build the generator executables on the native and make them available
# as a package when cross-compiling
if(NOT CMAKE_CROSSCOMPILING)
  add_executable(datafile
    datafile.c
  )
  target_link_libraries(datafile bme)
  add_executable(dat2inc
    dat2inc.c
  )
  export(TARGETS datafile dat2inc FILE "${CMAKE_BINARY_DIR}/MyGenConfig.cmake")
endif()
