C = gcc
CFLAGS = -Wall -g -std=c11 -lSDL2 -lSDL2_image `sdl2-config --cflags --libs`
SOURCES = load.c save.c
OBJS = $(SOURCES:%.c=%.o)

all: $(OBJS)

load.o: load.c load.h ../sdlutils.h
save.o : save.c save.h

cleanall:
	rm -rf *~ *.o $(OBJS)