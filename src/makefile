#
# Linux makefile
#

# NOTE: sdl2 is not actually used. It's a hack to force adding the macports
# include directory, which is missing from the the sdl.pc configuration.
# Alternative would be to modify all #includes from <SDL/SDL.h> to <SDL.h>.
CFLAGS=$(shell pkg-config --cflags sdl) $(shell pkg-config --cflags sdl2)
PREFIX=../linux/
SUFFIX=
LIBS=$(shell pkg-config --libs sdl)
EXTRA_OBJ=

include makefile.common
