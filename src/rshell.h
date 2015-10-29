#ifndef __RSHELL_H__ 
#define __RSHELL_H__

#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "rshell.h"

using namespace std;

//Virtual class for connectors
class connector
{
    protected:
        //Store whether or not the last command was successful
        bool ynSuccess;
        
    public:
        connector(bool ynSuccess)
        :ynSuccess(ynSuccess)
        {}
    
        virtual bool isGoodOrNot() = 0;
};

//Class which inherits from connector made for &&
class andConnector : public connector
{
    public:
        andConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        //If last command was successful then return true else return false
        bool isGoodOrNot()
        {
            return ynSuccess;
        }
};

//Class which inherits from connector made for ||
class orConnector : public connector
{
    public:
        orConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        //If last command was successful then return false else return true
        bool isGoodOrNot()
        {
            return !ynSuccess;
        }
};

//Class which inherits from connector made for ;
class semiColonConnector : public connector
{
    public:
        semiColonConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        //Always return true;
        bool isGoodOrNot()
        {
            return true;
        }
};

//Function which finds all the connectors in a char string and puts
//them in a queue
queue<char> findConnectors(char cmdCharString[])
{
    queue<char> connectorQueue;
    //Create a pointer pointing to the first occurance of a connector
    char* connectorPointer = strpbrk(cmdCharString, "|;&#");
    //Create a bool for keeping track of doubles
    bool conDoubCatcher = false;
    bool hashCatcher = false;
    //Loop to find all connectors and put them in the queue
    while (connectorPointer != NULL && hashCatcher == false)
    {
        //Make sure only one character is stored per connector
        if(!conDoubCatcher)
        {
            //Push connector character into command queue
            connectorQueue.push(*connectorPointer);
            if(*connectorPointer == '&' || *connectorPointer == '|')
                conDoubCatcher = true;
            else if(*connectorPointer == '#')
                hashCatcher = true;
                
            // //Print what is put into command queue for TESTING
            // cout << connectorQueue.back() << endl;
        }
        else
        {
            conDoubCatcher = false;
        }
        
        //Go to the next occurance of a connector character
        connectorPointer = strpbrk(connectorPointer + 1, "|;&#");
    }
    
    //return queue with all found connectors
    return connectorQueue;
}

queue<char*> findCommands(char cmdCharString[])
{
    queue<char*> commandQueue;
    //Create pointer to begining of first command
    char* cmdCharPointer = strtok(cmdCharString, "|;&#");
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
        cmdCharPointer = strtok (NULL, "|;&#");
    }
    
    return commandQueue;
}

//Function which seperates the command from other stuff and returns the command
char* createCommand(char* cmdCharPointer)
{
    //Seperate command from other stuff
    cmdCharPointer = strtok(cmdCharPointer, " ");
    
    // //Used for TESTING if command was separated properly
    // cout << cmdCharPointer << endl;
    
    //return command
    return cmdCharPointer;
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
    queue<char> connectorCharQueue = findConnectors(cmdCharString);
    
    //Create a queue filled with commands in order using findCommands()
    queue<char*> commandQueue = findCommands(cmdCharString);
    
    // //Create bool to store whether command execution was a success
    // bool ynSuccess = true;
    
    // //Run commands until we run out of commands to call
    // while(!commandQueue.empty())
    // {
    //     pid_t pid;
    //     int status;
        
    //     //Prepare command by seperating arguments from command
        
        
    //     //Run fork and get pid
    //     //If an error while forking occurs then say so and exit
    //     if ((pid = fork()) < 0) 
    //     {
    //         cout << "ERROR: forking child process failed" << endl;
    //         exit(1);
    //     }
    //     else if (pid == 0) 
    //     {
    //         //Run the command and record whether it was successful
    //         if(execvp(*argv, argv) < 0)
    //             ynSuccess = false;
    //         else
    //             ynSuccess = true;
    //     }
    //     else 
    //     {
    //         //Wait for completion
    //         while (wait(&status) != pid);
            
    //     }
    // }
    
    delete[] cmdCharString;
}

#endif