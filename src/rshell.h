#ifndef __RSHELL_H__ 
#define __RSHELL_H__

#include <queue>

//Function which finds all the connectors in a c-string and puts them in a queue
std::queue<char> findConnectors(char cmdCharString[]);

//Function which finds all the commands in a c-string and puts them in a queue
std::queue<char*> findCommands(char cmdCharString[]);

//Function to run the shell
void rshell();


#endif