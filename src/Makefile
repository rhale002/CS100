#Variables
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic

all: rshell

rshell: main.cpp rshell.h 
	$(COMPILE) $(FLAGS) -o rshell main.cpp rshell.h &&\
	if [ ! -d bin ]; then mkdir bin; fi && mv rshell bin
	
clean: 
	rm -rf *~ *.o bin