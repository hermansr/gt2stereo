cmake_minimum_required(VERSION 3.19)

configure_file(config.h.in config.h @ONLY)

add_executable(${PROJECT_NAME}
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
if(WIN32)
  target_sources(${PROJECT_NAME} PRIVATE gt2stereo.rc)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE asm bme resid)

add_executable(ins2snd2
  ins2snd2.c
)
target_link_libraries(ins2snd2 PRIVATE bme)

add_executable(mod2sng
  mod2sng2.c
)
target_link_libraries(mod2sng PRIVATE bme)

add_executable(ss2stereo
  ss2stereo.c
)
target_link_libraries(ss2stereo PRIVATE bme)

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

add_subdirectory(asm)
add_subdirectory(bme)
add_subdirectory(resid)
