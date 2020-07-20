C = gcc
CFLAGS = -Wall -g -std=c11 -lSDL2 -lSDL2_image `sdl2-config --cflags --libs`
SOURCES = main.c sdlutils.c view.c cli/cmdargs.c cli/cmdprocessing.c load_save/load.c load_save/save.c transformations/modification.c transformations/trans_couleurs.c
OBJS = $(SOURCES:%.c=%.o)
ALL = cimp

all: $(ALL)

cimp: $(OBJS)
	$(C) $(OBJS) $(CFLAGS) -o $@

main.o: main.c cli/cliconstants.h cli/cmdargs.h cli/cmdprocessing.h sdlutils.h
sdlutils.o: sdlutils.c sdlutils.h transformations/trans_couleurs.h cli/cmdprocessing.h cli/cmdargs.h load_save/save.h transformations/modification.h
view.o: view.c

cleanall:
	rm -rf *~ *.o $(OBJS) $(ALL)
	cd load_save && make cleanall
	cd cli && make cleanall