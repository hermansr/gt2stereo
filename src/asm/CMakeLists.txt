cmake_minimum_required(VERSION 3.5)

add_library(asm OBJECT
  asmtab.c
  chnkpool.c
  expr.c
  lexyy.c
  log.c
  membuf.c
  membufio.c
  namedbuf.c
  parse.c
  pc.c
  vec.c
)
target_include_directories(asm PUBLIC .)
