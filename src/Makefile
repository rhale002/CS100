#Variables
COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
OBJS = rshell.o

#Targets

all: main.cpp $(OBJS)
	$(COMPILE) $(FLAGS) -o rshell main.cpp $(OBJS);\
	if [ ! -d bin ]; then mkdir bin; fi; mv rshell bin

rshell: rshell.h rshell.cpp
	$(COMPILE) $(FLAGS) -c rshell.cpp
	
clean: 
	rm -rf *~ *.o bin