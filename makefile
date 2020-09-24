# CLASSDIR = $(HOME)
CLASSDIR = ./
INCLUDE = -I$(CLASSDIR)/kutuphaneler
LIBS = $(CLASSDIR)/kutuphaneler/libfdr.a
CC = gcc

EX = replace
all: $(EX) 
clean: 
	rm -f *.o $(EX)

replace: replace.o $(LIBS)
	$(CC) $(INCLUDE) -o replace replace.o $(LIBS)

.SUFFIXES: .c .o

.c.o: 
	$(CC) $(INCLUDE) -g  -c  $*.c

