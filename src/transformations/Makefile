C = gcc
CFLAGS = -Wall -g -std=c11 -lSDL2 -lSDL2_image `sdl2-config --cflags --libs`
SOURCES = load.c save.c
OBJS = $(SOURCES:%.c=%.o)

all: $(OBJS)

modification.o: modification.c modification.h
trans_couleurs.o : trans_couleurs.c trans_couleurs.h modification.h

cleanall:
	rm -rf *~ *.o $(OBJS)