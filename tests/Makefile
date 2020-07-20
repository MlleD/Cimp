C = gcc
CFLAGS = -Wall -g -std=c11 $(shell pkg-config --cflags sdl2 SDL2_image)
LDLIBS = -Wall $(shell pkg-config --libs check sdl2 SDL2_image) 
SOURCES = testcmdargs.c check_save.c check_modification.c check_trans_couleurs.c
OBJS = $(SOURCES:%.c=%.o)
ALL = $(OBJS:%.o=%)

all: $(ALL)

$(%.o): $(%.c)

testcmdargs: testcmdargs.o ../src/cli/cmdargs.o main_template.o

check_save: check_save.o ../src/load_save/save.o  ../src/load_save/load.o main_template.o

check_modification: check_modification.o ../src/transformations/modification.o ../src/load_save/load.o main_template.o

check_trans_couleurs: check_trans_couleurs.o ../src/transformations/trans_couleurs.o ../src/transformations/modification.o ../src/load_save/load.o main_template.o

cleanall:
	rm -rf *~ *.o $(OBJS) $(ALL)
	cd ../src/cli && make cleanall
	cd ../src/transformations && make cleanall