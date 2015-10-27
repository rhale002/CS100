#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include "rshell.h"

using namespace std;

void rshell()
{
    //Output Command prompt
    cout << "$ ";
    
    //Take in command
    string cmdString;
    getline(cin, cmdString);
    char cmdCharString[cmdString.size() + 1];
    strcpy(cmdCharString, cmdString.c_str());
    
    //Print endl for when TESTING with file
    cout << endl;
    
    queue<char> connectorQueue;
    char* connectorPointer = strpbrk(cmdCharString, "|;&");
    while (connectorPointer != NULL)
    {
        //Push connector character into command queue
        connectorQueue.push(*connectorPointer);
        
        // //Print what is put into command queue for TESTING
        // cout << connectorQueue.back() << endl;
        
        //Go to the next occurance of a connector character
        connectorPointer = strpbrk(connectorPointer + 1, "|;&");
    }
    
    //Create pointer to begining of first command
    char* cmdCharPointer = strtok(cmdCharString, "|;&");
    //Go through command cString
    while(cmdCharPointer != NULL)
    {
        //Get rid of space in begining of command
        while(*cmdCharPointer == ' ')
            cmdCharPointer++;
        
        // // Print command for TESTING
        // printf ("%s\n",cmdCharPointer);
        
        //Go to next command
        cmdCharPointer = strtok (NULL, "|;&");
    }
}