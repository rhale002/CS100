#ifndef __RSHELL_H__ 
#define __RSHELL_H__

#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include "rshell.h"

using namespace std;

//Function which finds all the connectors in a char string and puts
//them in a queue
queue<char> findConnectors(char cmdCharString[])
{
    queue<char> connectorQueue;
    //Create a pointer pointing to the first occurance of a connector
    char* connectorPointer = strpbrk(cmdCharString, "|;&");
    //Create a bool for keeping track of doubles
    bool conDoubCatcher = false;
    //Loop to find all connectors and put them in the queue
    while (connectorPointer != NULL)
    {
        //Make sure only one character is stored per connector
        if(!conDoubCatcher)
        {
            //Push connector character into command queue
            connectorQueue.push(*connectorPointer);
            if(*connectorPointer == '&' || *connectorPointer == '|')
                conDoubCatcher = true;
                
            // //Print what is put into command queue for TESTING
            // cout << connectorQueue.back() << endl;
        }
        else
        {
            conDoubCatcher = false;
        }
        
        //Go to the next occurance of a connector character
        connectorPointer = strpbrk(connectorPointer + 1, "|;&");
    }
    
    //return queue with all found connectors
    return connectorQueue;
}

queue<char*> findCommands(char cmdCharString[])
{
    queue<char*> commandQueue;
    //Create pointer to begining of first command
    char* cmdCharPointer = strtok(cmdCharString, "|;&");
    //Go through command cString and find commands
    while(cmdCharPointer != NULL)
    {
        //Get rid of space in begining of command
        while(*cmdCharPointer == ' ')
            cmdCharPointer++;
        
        commandQueue.push(cmdCharPointer);
        
        // // Print command for TESTING
        // cout << commandQueue.back() << endl;
        
        //Go to next command
        cmdCharPointer = strtok (NULL, "|;&");
    }
    
    return commandQueue;
}


//Function to run the shell
void rshell()
{
    //Output Command prompt
    cout << "$ ";
    
    //Take in command and store it in a c-string
    string cmdString;
    getline(cin, cmdString);
    char* cmdCharString = new char[cmdString.size()];
    strcpy(cmdCharString, cmdString.c_str());
    
    //Print endl for when TESTING with file
    cout << endl;
    
    //Create a queue filled with connectors in order using findConnectors()
    queue<char> connectorQueue = findConnectors(cmdCharString);
    
    //Create a queue filled with commands in order using findCommands()
    queue<char*> commandQueue = findCommands(cmdCharString);
    
    delete[] cmdCharString;
}

#endif