CC=g++
CFLAGS=-I.
DEPS = utility.h defs.h des.h
OBJ = utility.o des.o tcn5080project1.o
@INCLUDE = doxyfile.inc
SRCS =  utility.h defs.h utility.cpp tcn5080project1.cpp
SRCDIRS += $pwd 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sdes: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

oxy: doxyfile.inc $(SRCS)
