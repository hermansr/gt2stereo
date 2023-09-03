cmake_minimum_required(VERSION 3.19)

find_package(SDL)
if(NOT SDL_FOUND)
  # e.g. Fedora 38 does not provide a SDL CMake config file for MingW64
  message(STATUS "SDL not found using CMake config, falling back to pkg-config")
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(SDL REQUIRED sdl)
endif()

configure_file(config.h.in config.h)

include_directories(asm bme "${CMAKE_CURRENT_BINARY_DIR}" ${SDL_INCLUDE_DIRS})
add_compile_options(${SDL_CFLAGS_OTHER})

add_library(bme OBJECT
  bme/bme.c
  bme/bme_end.c
  bme/bme_gfx.c
  bme/bme_io.c
  bme/bme_kbd.c
  bme/bme_mou.c
  bme/bme_snd.c
  bme/bme_win.c
)

add_executable(${PROJECT_NAME}
  asm/asmtab.c
  asm/chnkpool.c
  asm/expr.c
  asm/lexyy.c
  asm/log.c
  asm/membuf.c
  asm/membufio.c
  asm/namedbuf.c
  asm/parse.c
  asm/pc.c
  asm/vec.c
  resid/dac.cc
  resid/envelope.cc
  resid/extfilt.cc
  resid/filter8580new.cc
  # resid/filter.cc
  resid/pot.cc
  resid/sid.cc
  # resid/version.cc
  resid/voice.cc
  resid/wave.cc
  gconsole.c
  gdisplay.c
  gfile.c
  ghelp.c
  ginstr.c
  goatdata.c
  gorder.c
  gpattern.c
  gplay.c
  greloc.c
  gsid.cpp
  gsong.c
  gsound.c
  gt2stereo.c
  gtable.c
)

target_link_libraries(${PROJECT_NAME} bme ${SDL_LIBRARIES} ${extra_libs})
target_link_options(${PROJECT_NAME} PUBLIC ${SDL_LDFLAGS_OTHER})
if(GT2_BUILD_WIN32)
  target_sources(${PROJECT_NAME} PRIVATE gt2stereo.rc)
  target_link_options(${PROJECT_NAME} PUBLIC -static-libgcc -static-libstdc++ -lssp)
  # -l ssp is to fix issue #2233205 with MinGW64 on Fedora 38
endif()

add_executable(ins2snd2
  ins2snd2.c
  bme/bme_end.c
)

add_executable(mod2sng
  mod2sng2.c
  bme/bme_end.c
)

add_executable(ss2stereo
  bme/bme_end.c
  ss2stereo.c
)

# only build the generator executables on the native and make them available
# as a package when cross-compiling
if(NOT CMAKE_CROSSCOMPILING)
  add_executable(datafile
    bme/datafile.c
    bme/bme_end.c
  )
  add_executable(dat2inc
    bme/dat2inc.c
  )
  export(TARGETS datafile dat2inc FILE
        "${CMAKE_BINARY_DIR}/MyGenConfig.cmake")
endif()

set(datasrc
  player.s
  altplayer.s
  chargen.bin
  palette.bin
  cursor.bin
  bcursor.bin
  goattrk2.bmp
)
list(TRANSFORM datasrc PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_custom_command(
  OUTPUT gt2stereo.dat
  COMMAND echo ${datasrc} > gt2stereo.seq
  COMMAND $<TARGET_FILE:datafile> gt2stereo.dat gt2stereo.seq
  DEPENDS datafile ${datasrc}
  VERBATIM)

add_custom_command(
  OUTPUT goatdata.c
  COMMAND $<TARGET_FILE:dat2inc> gt2stereo.dat goatdata.c
  DEPENDS dat2inc gt2stereo.dat
  VERBATIM)

install(TARGETS ${PROJECT_NAME} ins2snd2 mod2sng ss2stereo
    EXPORT ${PROJECT_NAME}
)
