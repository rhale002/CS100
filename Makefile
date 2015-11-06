#Variables
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
OBJS = rshell.o

all: rshell

rshell: 
	$(COMPILE) $(FLAGS) -c src/rshell.cpp &&\
	$(COMPILE) $(FLAGS) -o rshell src/main.cpp src/rshell.h $(OBJS) &&\
	if [ ! -d bin ]; then mkdir bin; fi && mv rshell bin && mv rshell.o bin
	
clean: 
	rm -rf *~ bin