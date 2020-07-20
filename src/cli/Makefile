C = gcc
CFLAGS = -Wall -g -std=c11
SOURCES = cmdargs.c cmdprocessing.c
OBJS = $(SOURCES:%.c=%.o) 

all: $(OBJS)

cmdargs.o: cmdargs.c cmdargs.h cliconstants.h
cmdprocessing.o: cmdprocessing.c cmdprocessing.h ../sdlutils.h ../load_save/load.h ../load_save/save.h ../transformations/modification.h ../view.h

cleanall:
	rm -rf *~ *.o $(OBJS)
	cd ../load_save && make cleanall