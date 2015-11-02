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
        
        virtual ~connector()
        {}
    
        virtual bool isGoodOrNot(bool ynSuccess) = 0;
};

//Class which inherits from connector made for &&
class andConnector : public connector
{
    public:
        andConnector()
        : connector(true)
        {}
    
        andConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        virtual ~andConnector()
        {}
        
        //If last command was successful then return true else return false
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            this->ynSuccess = ynSuccess;
            return this->ynSuccess;
        }
};

//Class which inherits from connector made for ||
class orConnector : public connector
{
    public:
        orConnector()
        : connector(true)
        {}
        
        orConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        virtual ~orConnector()
        {}
        
        //If last command was successful then return false else return true
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            this->ynSuccess = !ynSuccess;
            return this->ynSuccess;
        }
};

//Class which inherits from connector made for ;
class semiColonConnector : public connector
{
    public:
        semiColonConnector()
        : connector(true)
        {}
        
        semiColonConnector(bool ynSuccess)
        : connector(ynSuccess)
        {}
        
        virtual ~semiColonConnector()
        {}
        
        //Always return true;
        virtual bool isGoodOrNot(bool ynSuccess)
        {
            this->ynSuccess = true;
            return this->ynSuccess;
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
        
        //Go to next command
        cmdCharPointer = strtok (NULL, "|;&#");
    }
    
    return commandQueue;
}

//Creates a queue with the seperate arguments for a command
queue<char*> seperateCommand(char command[])
{
    queue<char*> sepComQueue;
    
    char* cmdCharPointer = strtok(command, " ");
    while(cmdCharPointer != NULL)
    {
        sepComQueue.push(cmdCharPointer);
        
        cmdCharPointer = strtok(NULL, " ");
    }
    
    return sepComQueue;
}

//Fills the 2D array with all arguments for running the command
void fillArgsArray(char** args, queue<char*> sepComQueue)
{
    unsigned i;
    for(i = 0; !sepComQueue.empty(); i++)
    {
        args[i] = sepComQueue.front();
        sepComQueue.pop();
    }
    args[i] = NULL;
}

//Runs the command and returns true if success else false
bool runCommand(char** args)
{
    //Create bool to store whether command execution was a success
    bool ynSuccess = true;
    
    pid_t pid;
    int status;
    
    //Run fork and get parent id
    //If an error while forking occurs then say so and exit
    if ((pid = fork()) < 0) 
    {
        cout << "ERROR: forking child process failed" << endl;
        exit(1);
    }
    else if (pid == 0) 
    {
        //Run the command
        execvp(*args, args);
    }
    else 
    {
        //Wait for completion
        while(wait(&status) != pid);
        
        //Tests if command executed properly and if not sets success to false
        if(WIFEXITED(status))
        {
            if(WEXITSTATUS(status) != 0)
                ynSuccess = false;
        }
        else
        {
            ynSuccess = false;
        }
    }
    
    return ynSuccess;
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
    queue<connector*> connectorQueue;
    while(!connectorCharQueue.empty())
    {
        if(connectorCharQueue.front() == '&')
        {
            andConnector* p = new andConnector();
            connectorQueue.push(p);
        }
        else if(connectorCharQueue.front() == '|')
        {
            orConnector* p = new orConnector();
            connectorQueue.push(p);
        }
        else
        {
            semiColonConnector* p = new semiColonConnector();
            connectorQueue.push(p);
        }
        connectorCharQueue.pop();
    }
    
    //Create a queue filled with commands in order using findCommands()
    queue<char*> commandQueue = findCommands(cmdCharString);
    
    //Create bool to store whether command execution was a success
    bool ynSuccess = true;
    
    //Run commands until we run out of commands to call
    while(!commandQueue.empty())
    {
        //Creates a queue with the seperate arguments for a command
        queue<char*> sepComQueue = seperateCommand(commandQueue.front());
        
        //Take one out of the queue of commands which need to be run
        commandQueue.pop();
        
        //Create a 2D array and store all arguments for command
        unsigned argsSize = sepComQueue.size() + 1;
        char** args = new char*[argsSize];
        fillArgsArray(args, sepComQueue);
        
        //If command is exit then exit
        if(strcmp(*args, "exit") == 0)
            exit(0);
        
        //Run the command and store whether it was a success
        ynSuccess = runCommand(args);
        
        //Handles connectors
        if(!connectorQueue.empty())
        {
            if(!(connectorQueue.front()->isGoodOrNot(ynSuccess)))
                commandQueue.pop();
            connector* p = connectorQueue.front();
            delete p;
            connectorQueue.pop();
        }
        
        delete[] args;
    }
    delete[] cmdCharString;
}

#endif