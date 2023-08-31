CC?=gcc
# NOTE: sdl2 is not actually used. It's a hack to force adding the macports
# include directory, which is missing from the the sdl.pc configuration.
# Alternative would be to modify all #includes from <SDL/SDL.h> to <SDL.h>.
CFLAGS+=$(shell pkg-config --cflags sdl) $(shell pkg-config --cflags sdl2)
LIBS+=$(shell pkg-config --libs sdl)


all: dat2inc datafile

datafile: datafile.c bme_end.c
	$(CC) $(CFLAGS) -o datafile datafile.c bme_end.c
	strip datafile

dat2inc: dat2inc.c
	$(CC) $(LIBS) -o dat2inc dat2inc.c
	strip dat2inc

