#Variables
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic

all: rshell

rshell: 
	$(COMPILE) $(FLAGS) -o rshell src/main.cpp src/rshell.h &&\
	if [ ! -d bin ]; then mkdir bin; fi && mv rshell bin
	
clean: 
	rm -rf *~ bin